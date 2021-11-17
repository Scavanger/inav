
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


#include "common/utils.h"
#include "common/axis.h"
#include "fc/fc_core.h"

#include "programming/programming_overrides.h"


EXTENDED_FASTRAM uint64_t programmingGlobalFlags;;
EXTENDED_FASTRAM int programmingValues[PROGRAMMING_VALUE_LAST];
EXTENDED_FASTRAM rcChannelOverride_t rcChannelOverrides[MAX_SUPPORTED_RC_CHANNEL_COUNT];

float NOINLINE getThrottleScale(float globalThrottleScale) {
    if (PROGRAMMING_GLOBAL_FLAG(PROGRAMMING_GLOBAL_FLAG_OVERRIDE_THROTTLE_SCALE)) {
        return constrainf(programmingValues[PROGRAMMING_VALUE_OVERRIDE_THROTTLE] / 100.0f, 0.0f, 1.0f);
    } else {
        return globalThrottleScale;
    }
}

int16_t getRcCommandOverride(int16_t command[], uint8_t axis) {
    int16_t outputValue = command[axis];

    if (PROGRAMMING_GLOBAL_FLAG(PROGRAMMING_GLOBAL_FLAG_OVERRIDE_SWAP_ROLL_YAW) && axis == FD_ROLL) {
        outputValue = command[FD_YAW];
    } else if (PROGRAMMING_GLOBAL_FLAG(PROGRAMMING_GLOBAL_FLAG_OVERRIDE_SWAP_ROLL_YAW) && axis == FD_YAW) {
        outputValue = command[FD_ROLL];
    }

    if (PROGRAMMING_GLOBAL_FLAG(PROGRAMMING_GLOBAL_FLAG_OVERRIDE_INVERT_ROLL) && axis == FD_ROLL) {
        outputValue *= -1;
    }
    if (PROGRAMMING_GLOBAL_FLAG(PROGRAMMING_GLOBAL_FLAG_OVERRIDE_INVERT_PITCH) && axis == FD_PITCH) {
        outputValue *= -1;
    }
    if (PROGRAMMING_GLOBAL_FLAG(PROGRAMMING_GLOBAL_FLAG_OVERRIDE_INVERT_YAW) && axis == FD_YAW) {
        outputValue *= -1;
    }

    return outputValue;
}

int16_t getRcChannelOverride(uint8_t channel, int16_t originalValue) {
    if (rcChannelOverrides[channel].active) {
        return rcChannelOverrides[channel].value;
    } else {
        return originalValue;
    }
}

void programmingOverridesReset(void)
{
    //Disable all flags
    programmingGlobalFlags = 0;

    for (uint8_t i = 0; i < MAX_SUPPORTED_RC_CHANNEL_COUNT; i++) {
        rcChannelOverrides[i].active = false;
    }
}
