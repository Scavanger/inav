/*
 * This file is part of INAV Project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Alternatively, the contents of this file may be used under the terms
 * of the GNU General Public License Version 3, as described below:
 *
 * This file is free software: you may copy, redistribute and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://www.gnu.org/licenses/.
 */
#include "platform.h"

#if defined(USE_USER_SCRIPT)

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "programming/user_script.h"
#include "programming/lua_script.h"
#include "common/utils.h"
#include "common/log.h"
#include "common/memory.h"

#define SCRIPT_FOLDER_NAME "scripts"
#define USER_SCRIPT_MAX_COUNT 10
#define USER_SCRIPT_ERROR_MSG_LENGTH 150
#define USER_SCRIPT_ERROR_MSG_QUEUE_COUNT 5

typedef enum {
    USER_SCRIPT_STATE_FS_INIT,
    USER_SCRIPT_STATE_FS_WAIT,
    USER_SCRIPT_STATE_FS_READY,
    USER_SCRIPT_STATE_LOAD_FILES,
    USER_SCRIPT_STATE_OK,
    USER_SCRIPT_STATE_ERROR
} userScriptState_t;

typedef struct {
    char filename[FAT_FILENAME_LENGTH + 1];
    uint32_t size;
    bool isActive;
    int ref;
    char *script;
} userScriptInfo_t;

typedef struct {
    userScriptInfo_t *scriptInfo;
    uint32_t size;
    uint8_t count;
    uint8_t activeScripts;
    uint8_t *buffer;
} userScript_t;

char errorMsgQuenue[USER_SCRIPT_ERROR_MSG_QUEUE_COUNT][USER_SCRIPT_ERROR_MSG_LENGTH];
int lastErrorMsgIdx = -1;
userScriptDbgPuts_t userScriptDbgPuts = NULL;
userScriptDbgPutc_t userScriptDbgPutc = NULL;
userScript_t userScripts;
userScriptState_t userScriptState = USER_SCRIPT_STATE_FS_INIT;
afatfsFilePtr_t scriptDirectory;
afatfsFilePtr_t scriptFile;
afatfsFinder_t scriptDirectoryFinder;

void userScriptInit(void) 
{
    userScripts.size = 0;
    userScripts.count = 0;
    userScripts.activeScripts = 0;
    userScripts.buffer = NULL;
    userScripts.scriptInfo = NULL;
    luaScriptInit();
}

void userScriptDisable(void) 
{
    userScriptState = USER_SCRIPT_STATE_ERROR;
}

static void scriptFolderOpenCallback(afatfsFilePtr_t folder) 
{
    if (folder) {
        scriptDirectory = folder;
        afatfs_findFirst(folder, &scriptDirectoryFinder);
    } else {
        userScriptSetErrorMsg("Error while opening scripts folder.");
        userScriptState = USER_SCRIPT_STATE_ERROR;
    }
}

static void scriptFileOpenCallback(afatfsFilePtr_t file)
{
    if (file) {
        scriptFile = file;
    } else {
        file = NULL;
    }
}

void userScriptRunOnce(bool debug)
{    
    if (userScripts.activeScripts == 0) {
        userScriptState = USER_SCRIPT_STATE_ERROR;
        return;
    }
    for (uint8_t i = 0; i < userScripts.count; i++) {
        if (userScripts.scriptInfo[i].isActive) {
            if (debug && userScriptDbgPuts != NULL) {
                userScriptDbgPuts(userScripts.scriptInfo[i].filename);
                userScriptDbgPuts(":\n");
            }
            if (!luaScriptExecuteScript(userScripts.scriptInfo[i].filename, userScripts.scriptInfo[i].ref)) {
                userScripts.scriptInfo[i].isActive = false;
                userScripts.activeScripts--;
            } 
        }
    }
}


void userScriptUpdateTask(timeUs_t currentTimeUs)
{
    fatDirectoryEntry_t *directoryEntry;
    UNUSED(currentTimeUs);   
    switch (userScriptState){      
        case USER_SCRIPT_STATE_FS_INIT: // Wait unitl SD card is initalized and check for errors
        {    
            afatfsFilesystemState_e fsState = afatfs_getFilesystemState();
            if (fsState == AFATFS_FILESYSTEM_STATE_FATAL || fsState == AFATFS_FILESYSTEM_STATE_UNKNOWN || afatfs_isFull()) {
                userScriptSetErrorMsg("SD card: fatal error or full.");
                userScriptState = USER_SCRIPT_STATE_ERROR;
                return;
            }
            if (fsState == AFATFS_FILESYSTEM_STATE_INITIALIZATION) {
                return;
            }
            if (fsState == AFATFS_FILESYSTEM_STATE_READY) {
                userScriptState = USER_SCRIPT_STATE_FS_READY;
                return;
            }
            userScriptSetErrorMsg("SD card: Unknown error.");
            userScriptState = USER_SCRIPT_STATE_ERROR; // Should never happen?!?
            break;
        }
        case USER_SCRIPT_STATE_FS_READY: // SD card is ready,
            if (!afatfs_mkdir(SCRIPT_FOLDER_NAME, scriptFolderOpenCallback)) {
                userScriptSetErrorMsg("Can't open or create script folder.");
                userScriptState = USER_SCRIPT_STATE_ERROR;
                break;
            }
            while(afatfs_findNext(scriptDirectory, &scriptDirectoryFinder, &directoryEntry) == AFATFS_OPERATION_SUCCESS) {
                if (directoryEntry && !fat_isDirectoryEntryTerminator(directoryEntry)) {
                    if (directoryEntry->fileSize > 0 &&
                        (directoryEntry->filename[8]  == 'L' && 
                         directoryEntry->filename[9]  == 'U' &&
                         directoryEntry->filename[10] == 'A' )) {
                        if (userScripts.count >= USER_SCRIPT_MAX_COUNT) {
                            userScriptSetErrorMsg("Maximum number of scripts (%d) reached, %s skipped", USER_SCRIPT_MAX_COUNT,  directoryEntry->filename);
                        } else {
                            userScripts.scriptInfo = memReallocate(userScripts.scriptInfo, (userScripts.count + 1) * sizeof(userScriptInfo_t));
                            if (!userScripts.scriptInfo) {
                                userScriptSetErrorMsg("Unable to allocate memory for script info");
                                userScriptState = USER_SCRIPT_STATE_ERROR;
                            } else {
                                strcpy(userScripts.scriptInfo[userScripts.count].filename, directoryEntry->filename);
                                userScripts.scriptInfo[userScripts.count].filename[FAT_FILENAME_LENGTH] = '\0';
                                userScripts.scriptInfo[userScripts.count].size = directoryEntry->fileSize;
                                userScripts.scriptInfo[userScripts.count].isActive = false;
                                userScripts.scriptInfo[userScripts.count].script = NULL;
                                userScripts.size += directoryEntry->fileSize;
                                userScripts.count++;
                            }
                        }
                    }
                } else {
                    afatfs_findLast(scriptDirectory);
                    if (userScripts.count > 0) {
                        userScriptState = USER_SCRIPT_STATE_LOAD_FILES;
                    } else {
                        userScriptSetErrorMsg("No user scripts found, user scripts disabled");
                        userScriptState = USER_SCRIPT_STATE_ERROR;
                        break;
                    }
                }
            }
            break;
        case USER_SCRIPT_STATE_LOAD_FILES:
            userScripts.buffer = memAllocate(userScripts.size + userScripts.count); // +1 per file for string terminator
            if (!userScripts.buffer) {
                userScriptSetErrorMsg("Can't allocate memory for script buffer.");
                userScriptState = USER_SCRIPT_STATE_ERROR;
                break;
            } 
            if (!afatfs_chdir(scriptDirectory)){
                userScriptSetErrorMsg("Can't change into scripts directory.");
                userScriptState = USER_SCRIPT_STATE_ERROR;
                break;
            }
            uint32_t pos = 0; 
            for (uint8_t i = 0; i < userScripts.count; i++) {     
                if (afatfs_fopen(userScripts.scriptInfo[i].filename, "r", scriptFileOpenCallback) && scriptFile != NULL) {         
                    if (afatfs_freadSync(scriptFile, (uint8_t*)(userScripts.buffer + pos), userScripts.scriptInfo[i].size) == userScripts.scriptInfo[i].size) {
                        userScripts.scriptInfo[i].script = (char*)(userScripts.buffer + pos);
                        pos += userScripts.scriptInfo[i].size;
                        userScripts.buffer[pos] = '\0';
                        pos++;
                    
                        if (luaScriptLoadScript(userScripts.scriptInfo[i].filename, userScripts.scriptInfo[i].script, &userScripts.scriptInfo[i].ref)) {
                            userScripts.scriptInfo[i].isActive = true;
                            userScripts.activeScripts++;
                        } else {
                            userScripts.scriptInfo[i].isActive = false;
                            userScriptSetErrorMsg("Error while loading %s", userScripts.scriptInfo[i].filename);
                        }   
                        
                        if (!afatfs_fclose(scriptFile, NULL)) {
                            userScriptSetErrorMsg("Can't close %s", userScripts.scriptInfo[i].filename);
                        }
                    } else {
                        userScriptSetErrorMsg("Unable to read %s.", userScripts.scriptInfo[i].filename);
                        afatfs_fclose(scriptFile, NULL);
                    }
                } else {
                    userScriptSetErrorMsg("Unable to open %s.", userScripts.scriptInfo[i].filename);
                }  
            }
            userScriptState = USER_SCRIPT_STATE_OK;
            break;
        case USER_SCRIPT_STATE_OK:
            userScriptRunOnce(false);
            break;
        case USER_SCRIPT_STATE_ERROR:
                if (userScripts.buffer) {
                    luaScriptClose();
                    memFree(userScripts.scriptInfo);
                    memFree(userScripts.buffer);
                    userScripts.buffer = NULL;
                }
            return;
        break;
        default:
            return;
    }
}

void userScriptDebug(userScriptDbgPuts_t cb)
{
    userScriptDbgPuts = cb;
    userScriptRunOnce(true);
    userScriptDbgPuts = NULL;
}

void userScriptPutc(const char c)
{
    LOG_E(USER_SCRIPT, &c);
    if (userScriptDbgPutc != NULL) {
        userScriptDbgPutc(c);
    }
}

void userScriptPuts(const char *s)
{
    LOG_E(USER_SCRIPT, s);
    if (userScriptDbgPuts != NULL) {
        userScriptDbgPuts(s);
    }
}

void userScriptSetErrorMsg(const char* format, ...)
{
    va_list args;
    
    lastErrorMsgIdx++;
    lastErrorMsgIdx %= USER_SCRIPT_ERROR_MSG_QUEUE_COUNT;    
    memset(errorMsgQuenue[lastErrorMsgIdx], '\0', USER_SCRIPT_ERROR_MSG_LENGTH);
    va_start(args, format);
    vsprintf(errorMsgQuenue[lastErrorMsgIdx], format, args);
    va_end(args);
    LOG_E(USER_SCRIPT, errorMsgQuenue[lastErrorMsgIdx]);
}

void userScriptGetAllErrors(userScriptDbgPuts_t cb)
{
     if (cb == NULL) {
         return;
    }

    if (lastErrorMsgIdx < 0) {
        cb("(No errors)");
        return;
    }

    int i = lastErrorMsgIdx;
    do {
        if(errorMsgQuenue[i][0] != '\0') {
            cb(errorMsgQuenue[i]); 
            cb("\n");
        }
        i--;
        if (i < 0) {
            i = USER_SCRIPT_ERROR_MSG_QUEUE_COUNT - 1;
        }
    } while (i != lastErrorMsgIdx);
}

void userScriptGetLastErrorMsg(userScriptDbgPuts_t cb) 
{
    if (lastErrorMsgIdx < 0 || cb == NULL) {
        return;
    }
    
    if (lastErrorMsgIdx < 0) {
        cb("(No errors)");
        return;
    }

    cb(errorMsgQuenue[lastErrorMsgIdx]);
    cb("\n");
    return;
}

bool userScriptisRunning(void)
{
    return userScriptState == USER_SCRIPT_STATE_OK;
}

#endif
