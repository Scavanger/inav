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

#include <string.h>
#include <setjmp.h>

#include "programming/lua/lua.h"
#include "programming/lua/lualib.h"
#include "programming/lua/lauxlib.h"
#include "common/utils.h"
#include "common/memory.h" 
#include "user_script.h"
#include "lua_script.h"

#define LUA_SCRIPT_MAX_INSTRUCTIONS 1000
// Expected errors in script
#define LUA_SCRIPT_ERROR(msg,...) userScriptSetErrorMsg(msg, __VA_ARGS__); goto error
// Unexpected errors in LUA interpretter
// We tinker us a try ... catch
jmp_buf *luaGlobalJumpBuf = NULL;
#define LUA_TRY_BEGIN   { jmp_buf localJmpBuf; \
                        luaGlobalJumpBuf = &localJmpBuf; \
                        if (setjmp(localJmpBuf) == 0) {
#define LUA_TRY_CATCH   } else {
#define LUA_TRY_END     } luaGlobalJumpBuf = NULL; }

lua_State *luaState;
bool maxInstructionsReached = false;

int luaPanicHandler(lua_State *L)
{
    if (luaGlobalJumpBuf){
        longjmp(*luaGlobalJumpBuf, 1);
    } else {
        userScriptSetErrorMsg("Unexpected LUA error (%s), user scripts disabeld.", lua_tostring(L, -1));
        userScriptDisable();
    }
    return 0;
}

void luaInstructionHook(lua_State *L, lua_Debug *ar)
{
    UNUSED(ar);
    maxInstructionsReached = true;
    lua_sethook(L, luaInstructionHook, LUA_MASKCOUNT, 1);
    luaL_error(L, "Script comsumend too much CPU time.");
}

void* luaScriptAlloc (void* ud, void* ptr, size_t osize, size_t nsize) {
    UNUSED(ud);
    UNUSED(osize);

    if (nsize == 0) {
        memFree(ptr);
        return NULL;
    } else {
        return memReallocate(ptr, nsize);
    }
}

bool luaScriptLoadScript(const char *filename, const char *script, int *loopRef) 
{
    *loopRef = 0;
    volatile bool returnValue = false;
    if (!luaState) {
        return returnValue;
    }
    maxInstructionsReached = false;
    lua_sethook(luaState, luaInstructionHook, LUA_MASKCOUNT, LUA_SCRIPT_MAX_INSTRUCTIONS);

    LUA_TRY_BEGIN
        int setupRef = 0;
        if (luaL_loadstring(luaState, script) != LUA_OK) {
            LUA_SCRIPT_ERROR("%s: Error while loading: %s", lua_tostring(luaState, -1));
        }   
        if (lua_pcall(luaState, 0, LUA_MULTRET, 0) != LUA_OK) {
            LUA_SCRIPT_ERROR("%s: Parsing error: %s", filename, lua_tostring(luaState, -1));
        }
        if (!lua_istable(luaState, -1)) {
            LUA_SCRIPT_ERROR("%s: No function table returned.", filename);
        }
        lua_pushnil(luaState);
        while(lua_next(luaState, -2)) {
            const char *key = lua_tostring(luaState, -2);
            if (lua_type(luaState, -1) != LUA_TFUNCTION) {
                break;
            }
            if (strcmp(key, "setup") == 0) {
                setupRef = luaL_ref(luaState, LUA_REGISTRYINDEX);
                lua_pushnil(luaState);
            } else if (strcmp(key, "loop") == 0) {
                *loopRef = luaL_ref(luaState, LUA_REGISTRYINDEX);
                lua_pushnil(luaState);
            }
            lua_pop(luaState, 1);
        }
        if (!*loopRef) {
            LUA_SCRIPT_ERROR("%s: No loop function found in function table.", filename);
        }
        if (setupRef) {
            lua_rawgeti(luaState, LUA_REGISTRYINDEX, setupRef);
            if (lua_pcall(luaState, 0, 0, 0) != LUA_OK) { 
                LUA_SCRIPT_ERROR("%s: Error in setup function: %s", filename, lua_tostring(luaState, -1));  
            }
            if (maxInstructionsReached) {
                LUA_SCRIPT_ERROR("%s: Setup function has consumed to much CPU time!", filename);     
            }
            luaL_unref(luaState, LUA_REGISTRYINDEX, setupRef);
            lua_gc(luaState, LUA_GCCOLLECT, 0);
        } 
        returnValue = true;

        error:
        if (!returnValue) {
            lua_pop(luaState, lua_gettop(luaState));
            if (setupRef){
                luaL_unref(luaState, LUA_REGISTRYINDEX, setupRef);
            }
        }  
    LUA_TRY_CATCH
        userScriptSetErrorMsg("%s: Fatal error while loading script: %s", filename, lua_tostring(luaState, -1));
        returnValue = false;
        userScriptDisable();
    LUA_TRY_END

    LUA_TRY_BEGIN
        lua_gc(luaState, LUA_GCCOLLECT, 0);
    LUA_TRY_CATCH
        userScriptSetErrorMsg("%s: GC error", filename);
        returnValue = false;
        userScriptDisable();
    LUA_TRY_END
    
    return returnValue;
}

bool luaScriptExecuteScript(const char* filename, int ref)
{
    volatile bool returnValue = false;
    if (!luaState){
        return returnValue;
    }
    maxInstructionsReached = false;
    lua_sethook(luaState, luaInstructionHook, LUA_MASKCOUNT, LUA_SCRIPT_MAX_INSTRUCTIONS);

    LUA_TRY_BEGIN
        int top = lua_gettop(luaState); 
        lua_rawgeti(luaState, LUA_REGISTRYINDEX, ref);
        if (lua_pcall(luaState, 0, LUA_MULTRET, 0) != LUA_OK) {
            LUA_SCRIPT_ERROR("%s: Error in loop function: %s", filename, lua_tostring(luaState, -1));
        }
        if (maxInstructionsReached) {
            LUA_SCRIPT_ERROR("%s: Loop function has consumed to much CPU time!", filename);
        }
        if (lua_gettop(luaState) - top != 1) {
            LUA_SCRIPT_ERROR("%s: Loop functions dosen't returned one result.", filename);
        }
        if (!lua_isnumber(luaState, -1)) {
            LUA_SCRIPT_ERROR("%s: Loop function dosen't returned an integer.", filename);
        }
        if (lua_tointeger(luaState, -1) != 0) {
            LUA_SCRIPT_ERROR("%s: Loop function dosen't returned zero.", filename);
        } 
        lua_pop(luaState, 1);
        returnValue = true;
        
        error:
        if (!returnValue) {
            lua_pop(luaState, lua_gettop(luaState));
            luaL_unref(luaState, LUA_REGISTRYINDEX, ref);
        }
    LUA_TRY_CATCH
        userScriptSetErrorMsg("%s: Fatal error while execute script: %s", filename, lua_tostring(luaState, -1));
        userScriptDisable();
    LUA_TRY_END

    LUA_TRY_BEGIN
        lua_gc(luaState, LUA_GCCOLLECT, 0);
    LUA_TRY_CATCH
        userScriptSetErrorMsg("%s: GC error", filename);
        returnValue = false;
        userScriptDisable();
    LUA_TRY_END

    return returnValue;
}

void luaScriptInit(void)
{  
    luaState = lua_newstate(luaScriptAlloc, NULL);
    if (luaState) {
        luaL_openlibs(luaState);
    } else {
        userScriptSetErrorMsg("Can't allocate memory for LUA, user scripts disabled.");
        userScriptDisable();
    }
}

void luaScriptClose(void)
{
    if (luaState){
        LUA_TRY_BEGIN
            lua_close(luaState);        
        LUA_TRY_CATCH 
            userScriptSetErrorMsg("Can't close LUA!");
        LUA_TRY_END
        luaState = NULL;
    } 
}

 #endif
