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

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "platform.h"

#if defined(USE_OSD) && defined(USE_SIMULATOR)

#include "common/utils.h"
#include "common/printf.h"
#include "common/time.h"
#include "common/bitarray.h"

#include "drivers/display.h"
#include "drivers/display_font_metadata.h"
#include "drivers/osd_symbols.h"

#include "config/parameter_group.h"
#include "config/parameter_group_ids.h"

#include "displayport_hitl.h"

#define ARRAY_OF_BITARRAYS(name, count, bits) bitarrayElement_t name[count][(bits + 31) / 32]
#define ARRAY_OF_BITARRAYS_CLR_ALL(name) memset(name, 0, sizeof(name))
#define ARRAY_OF_BITARRAYS_SET_ALL(name) memset(name, 0xffffffff, sizeof(name))
#define ARRAY_OF_BITARRAYS_GET(name, idx, bit) bitArrayGet(name[idx], bit)
#define ARRAY_OF_BITARRAYS_SET(name, idx, bit) bitArraySet(name[idx], bit)
#define ARRAY_OF_BITARRAYS_CLR(name, idx, bit) bitArrayClr(name[idx], bit)
#define ARRAY_OF_BITARRAYS_FIND_FIRST_SET(name, idx, startBit) BITARRAY_FIND_FIRST_SET(name[idx], startBit)

#define HITL_OSD_CLEAR_SCREEN 2
#define HITL_OSD_WRITE_STRING 3
#define HITL_OSD_DRAW_SCREEN 4

#define FONT_VERSION 3
#define ROWS 22
#define COLS 60
#define SCREENSIZE (ROWS*COLS)
#define TIMEOUT 1000

#define HITL_DP_OUT_BUF_SIZE 500
#define HITL_DP_MAX_SEND_SIZE 155

PG_REGISTER_WITH_RESET_TEMPLATE(hitlOsdConfig_t, hitlOsdConfig, PG_HITL_OSD_CONFIG, 1);
PG_RESET_TEMPLATE(hitlOsdConfig_t, hitlOsdConfig,
    .useHdOSD = 0,
);

static uint8_t cmdBuffer[HITL_DP_OUT_BUF_SIZE];
static uint8_t outBuf[HITL_DP_MAX_SEND_SIZE] = { 0 };
static uint16_t cmdBufferHead = 0;
static uint16_t cmdBufferTail = 0;
static bool isActive = false;
static bool counterPartPresent = false;
static bool reset = false;
static timeMs_t lastTransmitt = 0;

static displayPort_t hitlDisplayPort;
static uint8_t screen[ROWS][COLS];

static ARRAY_OF_BITARRAYS(extdChar, ROWS, COLS); // font isExtdChar for each character on the screen
static ARRAY_OF_BITARRAYS(dirty, ROWS, COLS); // change status for each character on the screen
static bool screenCleared;


static int output(uint8_t *subcmd, int len)
{
    if (isActive && len <= HITL_DP_OUT_BUF_SIZE) {        
        for (int i = 0; i < len; i++)
        {
           cmdBuffer[cmdBufferHead] = subcmd[i];
           cmdBufferHead = (cmdBufferHead + 1) % HITL_DP_OUT_BUF_SIZE;
        }    
        return len;
    } else {
        return 0;
    }
}

static int setChar(const uint8_t col, const uint8_t row, const uint16_t c)
{
    
    if (col < COLS && row < ROWS) {
        uint8_t ch = c & 0xFF;
        bool isExtdChar = (c >> 8);
        if (screen[row][col] != ch || ARRAY_OF_BITARRAYS_GET(extdChar, row, col) != isExtdChar) {
            screen[row][col] = ch;
            (isExtdChar) ? ARRAY_OF_BITARRAYS_SET(extdChar, row, col) : ARRAY_OF_BITARRAYS_CLR(extdChar, row, col);
            ARRAY_OF_BITARRAYS_SET(dirty, row, col);
        }
    }
    
    return 0;
}

static int writeChar(displayPort_t *displayPort, uint8_t col, uint8_t row, uint16_t c, textAttributes_t attr)
{
    UNUSED(displayPort); 
    UNUSED(attr);

    return setChar(col, row, c);
}

static int writeString(displayPort_t *displayPort, uint8_t col, uint8_t row, const char *string, textAttributes_t attr)
{
    UNUSED(displayPort);
    UNUSED(attr);

    while (*string) {
        setChar(col++, row, *string++);
    }
    return 0;
}

static void checkConnection(void)
{
    if (isActive && (millis() - lastTransmitt > TIMEOUT)) {
        isActive = false;
    }
}

static void zeroHitlDisplayPort(void)
{
    memset(screen, SYM_BLANK, sizeof(screen));
    ARRAY_OF_BITARRAYS_CLR_ALL(extdChar);
    ARRAY_OF_BITARRAYS_CLR_ALL(dirty);
}

static int clearScreen(displayPort_t *displayPort)
{
    UNUSED(displayPort);

    uint8_t subcmd[] = { HITL_OSD_CLEAR_SCREEN };

    zeroHitlDisplayPort();
    screenCleared = true;
    return output(subcmd, sizeof(subcmd));
}

static int drawScreen(displayPort_t *displayPort)
{
	for (size_t row = 0; row < ROWS; row++)
	{
		uint8_t count = 0;
		uint8_t dirtyCol = ARRAY_OF_BITARRAYS_FIND_FIRST_SET(dirty, row, 0);
		while (dirtyCol < COLS) {		
			uint8_t next = dirtyCol;
			uint8_t cmdIdx = 4;
			uint8_t rowCmd[COLS + 4]; 
			rowCmd[0] = HITL_OSD_WRITE_STRING;
			rowCmd[1] = row;
			rowCmd[2] = dirtyCol;
			bool isExtdChar = ARRAY_OF_BITARRAYS_GET(extdChar, row, dirtyCol);

			do {
				ARRAY_OF_BITARRAYS_CLR(dirty, row, dirtyCol);
				rowCmd[cmdIdx++] = screen[row][dirtyCol];

				if (ARRAY_OF_BITARRAYS_GET(dirty, row, ++next)) {
					dirtyCol = next;
				}

			} while(dirtyCol == next && ARRAY_OF_BITARRAYS_GET(extdChar, row, dirtyCol) == isExtdChar);

			rowCmd[3] = 0;
			rowCmd[3] = isExtdChar << 7;
			rowCmd[3] |= cmdIdx - 4;			
			output(rowCmd, cmdIdx);
            count++;
			dirtyCol = ARRAY_OF_BITARRAYS_FIND_FIRST_SET(dirty, row, next);
		}
	}

    checkConnection();

    if (reset) {
        clearScreen(displayPort);
        reset = false;
    }
    
    return 0;
}

static bool readChar(displayPort_t *displayPort, uint8_t col, uint8_t row, uint16_t *c, textAttributes_t *attr)
{
    UNUSED(displayPort);

    if (col >= COLS && row >= ROWS) {
        return false;
    }

    *c = screen[row][col];
    if (ARRAY_OF_BITARRAYS_GET(extdChar, row, col)) {
        *c |= 0x100;
    }

    if (attr) {
        *attr = TEXT_ATTRIBUTES_NONE;
    }

    return true;
}

static int grab(displayPort_t *displayPort)
{
    UNUSED(displayPort);
    return 0;
}

static textAttributes_t supportedTextAttributes(const displayPort_t *displayPort)
{
    UNUSED(displayPort);
    return TEXT_ATTRIBUTES_NONE;
}

static int release(displayPort_t *displayPort)
{
    UNUSED(displayPort);
    return 0;
}

static bool isTransferInProgress(const displayPort_t *displayPort)
{
    UNUSED(displayPort);
    return false;
}

static bool isReady(displayPort_t *displayPort)
{
    UNUSED(displayPort);
    return isActive;
}


static int heartbeat(displayPort_t *displayPort)
{
    UNUSED(displayPort);
    return 0;
}

static uint32_t txBytesFree(const displayPort_t *displayPort)
{
    UNUSED(displayPort);
    return UINT32_MAX;
}

static int screenSize(const displayPort_t *displayPort)
{
    UNUSED(displayPort);
    return SCREENSIZE;
}

static bool getFontMetadata(displayFontMetadata_t *metadata, const displayPort_t *displayPort)
{
    UNUSED(displayPort);
    metadata->charCount = 512;
    metadata->version = FONT_VERSION;
    return true;
}

static void resync(displayPort_t *displayPort)
{
    displayPort->rows = ROWS;
    displayPort->cols = COLS;
}

static const displayPortVTable_t hitlDisplayPortvTable = {
    .grab = grab,
    .release = release,
    .clearScreen = clearScreen,
    .drawScreen = drawScreen,
    .screenSize = screenSize,
    .writeString = writeString,
    .writeChar = writeChar,
    .readChar = readChar,
    .isTransferInProgress = isTransferInProgress,
    .heartbeat = heartbeat,
    .resync = resync,
    .txBytesFree = txBytesFree,
    .supportedTextAttributes = supportedTextAttributes,
    .getFontMetadata = getFontMetadata,
    .isReady = isReady,
};

displayPort_t* hitlDisplayPortInit(void)
{
    zeroHitlDisplayPort();
    displayInit(&hitlDisplayPort, &hitlDisplayPortvTable);
    hitlDisplayPort.displayPortType = HITL_DISPLAYPORT_TYPE;
    return &hitlDisplayPort;
}

void hitlDisplayportForceRedraw(void)
{
   clearScreen(NULL);
   cmdBufferHead = cmdBufferTail = 0;
}

uint8_t *hitlDisplayportGetOutCmd(uint16_t *length)
{   
    if (counterPartPresent && !isActive){
        reset = true;
    }

    //Assume commmand is transmitted immediately
    lastTransmitt = millis();
    counterPartPresent = isActive = true;
    *length = 0;
    while (cmdBufferHead != cmdBufferTail && *length < HITL_DP_MAX_SEND_SIZE)
    {  
       outBuf[(*length)++] = cmdBuffer[cmdBufferTail];
       cmdBufferTail = (cmdBufferTail + 1) % HITL_DP_OUT_BUF_SIZE;
    }

    if (*length == 0) {
        *length = 1;
        outBuf[0] = HITL_OSD_DRAW_SCREEN;
    }
    
    return outBuf;
}

#endif