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

#pragma once

#include "rx/rx.h"

typedef enum {
    PROGRAMMING_GLOBAL_FLAG_OVERRIDE_ARMING_SAFETY  = (1 << 0),
    PROGRAMMING_GLOBAL_FLAG_OVERRIDE_THROTTLE_SCALE = (1 << 1),
    PROGRAMMING_GLOBAL_FLAG_OVERRIDE_SWAP_ROLL_YAW  = (1 << 2),
    PROGRAMMING_GLOBAL_FLAG_OVERRIDE_INVERT_ROLL    = (1 << 3),
    PROGRAMMING_GLOBAL_FLAG_OVERRIDE_INVERT_PITCH   = (1 << 4),
    PROGRAMMING_GLOBAL_FLAG_OVERRIDE_INVERT_YAW     = (1 << 5),
    PROGRAMMING_GLOBAL_FLAG_OVERRIDE_THROTTLE       = (1 << 6),
    PROGRAMMING_GLOBAL_FLAG_OVERRIDE_OSD_LAYOUT     = (1 << 7),
    PROGRAMMING_GLOBAL_FLAG_OVERRIDE_RC_CHANNEL     = (1 << 8),
} programmingConditionsGlobalFlags_t;

typedef enum {
    PROGRAMMING_VALUE_THROTTLE_SCALE,
    PROGRAMMING_VALUE_VTX_POWER_LEVEL,
    PROGRAMMING_VALUE_VTX_BAND,
    PROGRAMMING_VALUE_VTX_CHANNEL,
    PROGRAMMING_VALUE_OVERRIDE_THROTTLE,
    PROGRAMMING_VALUE_OSD_LAYLOUT,
    PROGRAMMING_VALUE_LAST
} programmingValues_t;

typedef struct rcChannelOverride_s {
    uint8_t active;
    int value;
} rcChannelOverride_t;

extern uint64_t programmingGlobalFlags;
extern int programmingValues[PROGRAMMING_VALUE_LAST];
extern rcChannelOverride_t rcChannelOverrides[MAX_SUPPORTED_RC_CHANNEL_COUNT];

#define PROGRAMMING_GLOBAL_FLAG_DISABLE(mask)   (programmingGlobalFlags &= ~(mask))
#define PROGRAMMING_GLOBAL_FLAG_ENABLE(mask)    (programmingGlobalFlags |= (mask))
#define PROGRAMMING_GLOBAL_FLAG(mask)           (programmingGlobalFlags & (mask))

void programmingOverridesReset(void);
float getThrottleScale(float globalThrottleScale);
int16_t getRcCommandOverride(int16_t command[], uint8_t axis);
int16_t getRcChannelOverride(uint8_t channel, int16_t originalValue);
