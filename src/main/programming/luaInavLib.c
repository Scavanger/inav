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

#include "programming/lua/lua.h"
#include "programming/lua/lualib.h"
#include "programming/lua/lauxlib.h"

#include "programming/user_script.h"
#include "programming/programming_overrides.h"
#include "programming/global_variables.h"

#include "common/utils.h"
#include "common/maths.h"
#include "io/vtx.h"
#include "drivers/vtx_common.h"
#include "rx/rx.h"
#include "drivers/io_port_expander.h"
#include "common/axis.h"
#include "flight/pid.h"
#include "flight/imu.h"
#include "fc/fc_core.h"
#include "fc/rc_controls.h"
#include "fc/rc_modes.h"
#include "navigation/navigation.h"
#include "navigation/navigation_private.h"
#include "sensors/battery.h"
#include "sensors/pitotmeter.h"
#include "sensors/diagnostics.h"
#include "io/gps.h"
#include "io/osd_common.h"

/*** iNav LUA API
@module iNavLuaApi
*/ 

/***
 Get GVAR (global variable) value
 @function setGvar
 @tparam integer index Index of GVAR
 @treturn integer Value of GVAR
 */
static int inavGetGvar(lua_State *L)
{
    int index = luaL_checkinteger(L, 1);
    lua_pushinteger(L, gvGet(index));
    return 1;
}

/***
 Set GVAR (global variable) value
 @function setGvar
 @tparam integer index Index of GVAR to be set
 @tparam integer value Value of GVAR
 */
static int inavSetGvar(lua_State *L)
{
    int index = luaL_checkinteger(L, 1);
    int value = luaL_checkinteger(L, 2);
    gvSet(index, value);
    return 0;
}

/***
Override throttle scale
@function overrideThrottleScale
@tparam integer throttleScale Throttle scale in percent (value 0 - 100)
*/
static int inavOverrideThrottleScale(lua_State *L)
{ 
    PROGRAMMING_GLOBAL_FLAG_ENABLE(PROGRAMMING_VALUE_THROTTLE_SCALE);
    programmingValues[PROGRAMMING_VALUE_THROTTLE_SCALE] = luaL_checkinteger(L, 1);
    return 0;
}

/***
Override arming saftey, allows to arm on any angle even without GPS fix
@function overrideArmingSafety
*/
static int inavOverrideArmingSafety(lua_State *L)
{
    UNUSED(L);
    PROGRAMMING_GLOBAL_FLAG_ENABLE(PROGRAMMING_GLOBAL_FLAG_OVERRIDE_ARMING_SAFETY);
    return 0;
}

/***
Swap roll and yaw, basically, when activated, yaw stick will control roll and roll stick will control yaw. 
Required for tail-sitters VTOL during vertical-horizonral transition when body frame changes.
@function swapRollYaw
*/
static int inavSwapRollYaw(lua_State *L)
{
    UNUSED(L);
    PROGRAMMING_GLOBAL_FLAG_ENABLE(PROGRAMMING_GLOBAL_FLAG_OVERRIDE_SWAP_ROLL_YAW);
    return 0;
}


/***
Sets VTX power level
@function setVTXPowerLevel
@tparam integer index Index of powerlevel, values are 1-5 for SmartAudio and Tramp protocol
*/
static int inavSetVTXPowerLevel(lua_State *L)
{
#if defined(USE_VTX_SMARTAUDIO) || defined(USE_VTX_TRAMP)
    vtxDeviceCapability_t vtxDeviceCapability;
    int value = luaL_checkinteger(L, 1);   
    if (programmingValues[PROGRAMMING_VALUE_VTX_POWER_LEVEL] != value &&
        vtxCommonGetDeviceCapability(vtxCommonDevice(), &vtxDeviceCapability)) {
            programmingValues[PROGRAMMING_VALUE_VTX_POWER_LEVEL] = constrain(value, VTX_SETTINGS_MIN_POWER, vtxDeviceCapability.powerCount);
            vtxSettingsConfigMutable()->power = programmingValues[PROGRAMMING_VALUE_VTX_POWER_LEVEL];
    }
#endif
    return 0;
}

/***
Sets VTX band.
@function setVTXBand
@tparam integer index Index of band, values are 1-5
*/
static int inavSetVTXBand(lua_State *L)
{
    vtxDeviceCapability_t vtxDeviceCapability;
    int value = luaL_checkinteger(L, 1);
    if (programmingValues[PROGRAMMING_VALUE_VTX_BAND] != value && 
        vtxCommonGetDeviceCapability(vtxCommonDevice(), &vtxDeviceCapability)) {
            programmingValues[PROGRAMMING_VALUE_VTX_BAND] = constrain(value, VTX_SETTINGS_MIN_BAND, VTX_SETTINGS_MAX_BAND);
            vtxSettingsConfigMutable()->band = programmingValues[PROGRAMMING_VALUE_VTX_BAND];
    }
    return 0;
}

/***
Sets VTX channel.
@function setVTXChannel
@tparam integer index Index of channel, values are 1-8
*/
static int inavSetVTXChannel(lua_State *L)
{
    vtxDeviceCapability_t vtxDeviceCapability;
    int value = luaL_checkinteger(L, 1);
    if (programmingValues[PROGRAMMING_VALUE_VTX_CHANNEL] != value && 
        vtxCommonGetDeviceCapability(vtxCommonDevice(), &vtxDeviceCapability)) {
            programmingValues[PROGRAMMING_VALUE_VTX_CHANNEL] = constrain(value, VTX_SETTINGS_MIN_CHANNEL, VTX_SETTINGS_MAX_CHANNEL);
            vtxSettingsConfigMutable()->band = programmingValues[PROGRAMMING_VALUE_VTX_CHANNEL];
    }
    return 0;
}

/***
Inverts ROLL axis input for PID/PIFF controller
@function invertRoll
*/
static int inavInvertRoll(lua_State *L)
{
    UNUSED(L);
    PROGRAMMING_GLOBAL_FLAG_ENABLE(PROGRAMMING_GLOBAL_FLAG_OVERRIDE_INVERT_ROLL);
    return 0;
}

/***
Inverts YAW axis input for PID/PIFF controller
@function invertYaw
*/
static int inavInvertYaw(lua_State *L)
{
    UNUSED(L);
    PROGRAMMING_GLOBAL_FLAG_ENABLE(PROGRAMMING_GLOBAL_FLAG_OVERRIDE_INVERT_YAW);
    return 0;
}

/***
Inverts PITCH axis input for PID/PIFF controller
@function invertPitch
*/
static int inavInvertPitch(lua_State *L)
{
    UNUSED(L);
    PROGRAMMING_GLOBAL_FLAG_ENABLE(PROGRAMMING_GLOBAL_FLAG_OVERRIDE_INVERT_PITCH);
    return 0;
}

/***
Override throttle value that is feed to the motors by mixer
@function overrideThrottle
@tparam integer value New value in us, 1000 means throttle cut, 1500 means half throttle
*/ 
static int inavOverrideThrottle(lua_State *L)
{
    int value = luaL_checkinteger(L, 1);
    programmingValues[PROGRAMMING_VALUE_OVERRIDE_THROTTLE] = value;
    PROGRAMMING_GLOBAL_FLAG_ENABLE(PROGRAMMING_VALUE_OVERRIDE_THROTTLE);
    return 0;
}

/***
Sets OSD layout
@function setOSDLayout
@tparam integer index Index of selected OSD layout, accepted values are 0-3
*/
static int inavSetOSDLayout(lua_State *L)
{
    int value = luaL_checkinteger(L, 1);
    programmingValues[PROGRAMMING_VALUE_OSD_LAYLOUT] = value;
    PROGRAMMING_GLOBAL_FLAG_ENABLE(PROGRAMMING_VALUE_OSD_LAYLOUT);
    return 0;
}

/***
Set I2C IO Expander
@function portSet
@tparam integer pin Pin, accepted values are 0 - 7
@tparam bool value Pin value
*/
static int inavSetPort(lua_State *L)
{
#ifdef USE_I2C_IO_EXPANDER
    int pin = luaL_checkinteger(L, 1);
    int value = lua_toboolean(L, 2); 
    ioPortExpanderSet(pin, value);
#else
    lua_pop(L, lua_gettop(L));
#endif
    return 0;
}

/***
Overrides an RC channel
@function rcChannelOverride
@tparam integer channel Index of channel, accepted values are 1 - 18
@tparam integer value Value of chennel in us, accepted values are 1000 - 2000
*/
static int inavRcChannelOverride(lua_State *L)
{
    int channel = luaL_checkinteger(L, 1);
    int value = luaL_checkinteger(L, 2);
    int idx = constrain(channel - 1, 0, MAX_SUPPORTED_RC_CHANNEL_COUNT - 1);
    rcChannelOverrides[idx].active = true;
    rcChannelOverrides[idx].value = constrain(value, PWM_RANGE_MIN, PWM_RANGE_MAX);
    PROGRAMMING_GLOBAL_FLAG_ENABLE(PROGRAMMING_GLOBAL_FLAG_OVERRIDE_RC_CHANNEL);
    return 0;
}

/***
Sets heading-hold target
@function setHeadingTarget
@tparam integer degree New target in degrees. Value wraps-around.
*/
static int inavSetHeadingTarget(lua_State *L)
{
    int value = luaL_checkinteger(L, 1);
    int degrees = CENTIDEGREES_TO_DEGREES(wrap_36000(DEGREES_TO_CENTIDEGREES(value)));
    updateHeadingHoldTarget(degrees); 
    return 0;
}

/***
Get flight time
@function getFlightTime
@treturn integer Flight time in seconds
*/
static int inavGetFlightTime(lua_State *L)
{ 
    lua_pushinteger(L, getFlightTime());
    return 1;
}

/***
Get arm time
@function getArmTime
@treturn integer Arm time in seconds
*/
static int inavGetArmTime(lua_State *L)
{
    lua_pushinteger(L, getArmTime());
    return 1;
}

/***
Get distance to home
@function getDistanceToHome
@treturn integer Distance to home in meters
*/
static int inavGetDistanceToHome(lua_State *L)
{
    lua_pushinteger(L, GPS_distanceToHome);
    return 1;
}

/***
Get total travel distance
@function getDistanceToHome
@treturn integer Total travel distance in meters
*/
static int inavGetTripDistance(lua_State *L)
{
    lua_pushinteger(L, getTotalTravelDistance() / 100);
    return 1;
}

/***
Get Rssi
@function getRssi
@treturn integer Rssi in percent (0 - 99)
*/
static int inavGetRssi(lua_State *L)
{
    lua_pushinteger(L, constrain(getRSSI() * 100 / RSSI_MAX_VALUE, 0, 99));
    return 1;
}

/***
Get battery voltage (VBat)
@function getVbat
@treturn integer VBat in volts * 100 (eg. 12.1 V is 1210)
*/
static int inavGetVbat(lua_State *L)
{
    lua_pushinteger(L, getBatteryVoltage());
    return 1;
}
/***
Get cell voltage
@function getCellVoltage
@treturn integer Average voltage per cell * 100 (e.g. 3.1V is 310)
*/
static int inavGetCellVoltage(lua_State *L)
{
    lua_pushinteger(L, getBatteryRawAverageCellVoltage());
    return 1;
}

/***
Get cell count
@function getCellCount
@treturn integer Number of battery cells
*/
static int inavGetCellCount(lua_State *L)
{
    lua_pushinteger(L, getBatteryCellCount());
    return 1;
}

/***
Get current amperage
@function getCurrentAmperage
@treturn integer Current amperage * 100 (e.g. 23 A is 2300)
*/
static int inavgGetCurrentAmperage(lua_State *L)
{
    lua_pushinteger(L, getAmperage());
    return 1;
}

/***
Get Current drawn
@function getCurrentDrawn
@treturn integer rCurrent drawn in mAh
*/
static int inavGetCurrentDrawn(lua_State *L)
{
    lua_pushinteger(L, getMAhDrawn());
    return 1;
}

/***
Get number of GPS sattelites
@function getGpsSats
@treturn integer Number of GPS sattelites
*/
static int inavGetGpsSats(lua_State *L)
{
    int sats = 0;
    if (getHwGPSStatus() == HW_SENSOR_OK) {
        sats = gpsSol.numSat;
    }
    lua_pushinteger(L, sats);
    return 1;
}

/***
Get Status of GPS fix
@function getGpsFix
@treturn bool TRUE if GPS has fix
*/
static int inavIsGpsFix(lua_State *L)
{
    lua_pushboolean(L, STATE(GPS_FIX));
    return 1;
}

/***
Gets speed over ground
@function getGroundSpeed
@treturn integer Speed pver ground in cm/s
*/
static int inavGetGroundSpeed(lua_State *L)
{
    lua_pushinteger(L, gpsSol.groundSpeed);
    return 1;
}

/***
Get 3D speed
@function get3DSpeed
@treturn integer Speed over ground in cm/s
*/
static int inavGet3DSpeed(lua_State *L)
{
    lua_pushinteger(L, osdGet3DSpeed());
    return 1;
}

/***
Get air speed
@function getAirSpeed
@treturn integer Air speed in cm/s
*/
static int inavGetAirSpeed(lua_State *L)
{
    lua_Number speed = 0;
#ifdef USE_PITOT
    speed = pitot.airSpeed;
#endif
    lua_pushinteger(L, speed);
    return 1;
}

/***
Get flight altitude
@function getFlightAltitude
@treturn integer Flight altitude in cm
*/
static int inavGetFlightAltitude(lua_State *L)
{
    lua_pushinteger(L, getEstimatedActualPosition(Z));
    return 1;
}

/***
Get vertical speed
@function getVerticalSpeed
@treturn integer Vertical speed im cm/s
*/
static int inavGetVerticalSpeed(lua_State *L)
{
    lua_pushinteger(L, getEstimatedActualVelocity(Z));
    return 1;
}

/***
Get flight throttle position
@function getFlightThrottlePos
@treturn integer Throttle position in %
*/
static int inavGetFlightThrottlePos(lua_State *L)
{
    lua_pushinteger(L, (constrain(rcCommand[THROTTLE], PWM_RANGE_MIN, PWM_RANGE_MAX) - PWM_RANGE_MIN) * 100 / (PWM_RANGE_MAX - PWM_RANGE_MIN));
    return 1;
}


/***
Get flight attitude of pitch axis 
@function getFlightAttitiudePitch
@treturn integer Roll attitude in degrees
*/
static int inavGetFlightAttitiudePitch(lua_State *L)
{
    lua_pushinteger(L, constrain(attitude.values.pitch / 10, -180, 180));
    return 1;
}

/***
Get flight attitude of roll axis 
@function getFlightAttitiudeRoll
@treturn integer Roll attitude in degrees
*/
static int inavGetFlightAttitiudeRoll(lua_State *L)
{
    lua_pushinteger(L, constrain(attitude.values.roll / 10, -180, 180));
    return 1;
}


/***
Get arm status
@function isArmed
@treturn bool TRUE if aircraft is armed
*/
static int inavIsArmed(lua_State *L)
{
    lua_pushboolean(L, ARMING_FLAG(ARMED));
    return 1;
}

/***
Get autolaunch status
@function isAutolaunch
@treturn bool TRUE if autolaunch is active
*/
static int inavIsAutolaunch(lua_State *L)
{
    lua_pushboolean(L, navGetCurrentStateFlags() & NAV_CTL_LAUNCH);
    return 1;
}

/***
Get altitude control status
@function isAltitudeControl
@treturn bool TRUE if altitude control is active
*/
static int inavIsAltitudeControl(lua_State *L)
{
    lua_pushboolean(L, navGetCurrentStateFlags() & NAV_CTL_ALT);
    return 1;
}

/***
Get position control status
@function isPostionControl
@treturn bool TRUE if position control is active
*/
static int inavIsPostionControl(lua_State *L)
{
    lua_pushboolean(L, navGetCurrentStateFlags() & NAV_CTL_POS);
    return 1;
}

/***
Get emergency landing status
@function isEmergecyLanding
@treturn bool TRUE if emergency landing is active
*/
static int inavIsEmergecyLanding(lua_State *L)
{
    lua_pushboolean(L, navGetCurrentStateFlags() & NAV_CTL_EMERG);
    return 1;
}

/***
Get return to home status
@function isRTH
@treturn bool TRUE if return to home is active
*/
static int inavIsRTH(lua_State *L)
{
    lua_pushboolean(L, navGetCurrentStateFlags() & NAV_AUTO_RTH);
    return 1;
}

/***
Get waypoint status
@function isWaypoint
@treturn bool TRUE if waypoint mode is active
*/
static int inavIsWaypoint(lua_State *L)
{
    lua_pushboolean(L, navGetCurrentStateFlags() & NAV_AUTO_WP);
    return 1;
}

/***
Get landing status
@function isLanding
@treturn bool TRUE if landing is active
*/
static int inavIsLanding(lua_State *L)
{
    lua_pushboolean(L, navGetCurrentStateFlags() & NAV_CTL_LAND);
    return 1;
}

/***
Get failsafe status
@function isfailsafe
@treturn bool TRUE if failsafe is active
*/
static int inavIsfailsafe(lua_State *L)
{
    lua_pushboolean(L, failsafePhase() != FAILSAFE_IDLE);
    return 1;
}

/***
Get output of PID controller of selected axis
@function getPidOut
@tparam integer axis, Use fields yaw, pitch or roll
@treturn integer Pid Output (-500 - 500) 
*/
static int inavGetPidOut(lua_State *L)
{
    int axis = luaL_checkinteger(L, 1);
    lua_pushinteger(L, axisPID[axis]);
    return 1;
}

/***
Get waypoint action
@function getWaypointAction 
@treturn integer One of WP_* fields
*/
static int inavGetWaypointAction(lua_State *L)
{
    lua_pushinteger(L, NAV_Status.activeWpAction);
    return 1;
}

/***
Get index of current waypoint
@function getWpIndex
@treturn integer Index of current waypoint, starts with 1
*/
static int inavGetWpIndex(lua_State *L)
{
    lua_pushinteger(L, NAV_Status.activeWpNumber);
    return 1;
}

/***
Get 3D home distance
@function get3dHomeDistance
@treturn integer Distance to home (3D) im meter
*/
static int inavGet3dHomeDistance(lua_State *L)
{
    lua_pushinteger(L, fast_fsqrtf(sq(GPS_distanceToHome) + sq(getEstimatedActualPosition(Z)/100)));
    return 1;
}

/***
Get Crossfire LQ
@function getCrsfLQ
@treturn integer Crossfire LQ
*/
static int inavGetCrsfLQ(lua_State *L)
{
    int value = 0;
#ifdef USE_SERIALRX_CRSF
    value = rxLinkStatistics.uplinkLQ;
#endif
    lua_pushinteger(L, value);
    return 1;
}

/***
Get Crossfire SNR
@function getCrsfSNR
@treturn integer Crossfire SNR
*/
static int inavGetCrsfSNR(lua_State *L)
{
    int value = 0;
#ifdef USE_SERIALRX_CRSF
    value = rxLinkStatistics.uplinkSNR;
#endif
    lua_pushinteger(L, value);
    return 1;
}

typedef enum {
    LUA_FM_NONE,
    LUA_FM_FAILSAFE,
    LUA_FM_MANUAL,
    LUA_FM_NAV_RTH,
    LUA_FM_NAV_POSHOLD,
    LUA_FM_NAV_COURSE_HOLD,
    LUA_FM_CRUISE,
    LUA_FM_ALTHOLD,
    LUA_FM_ANGLE,
    LUA_FM_HORIZON,
    LUA_FM_AIR,
    LUA_FM_USER1,
    LUA_FM_USER2, 
} lua_flightMode_t;

static inline void pushFlightMode(lua_State *L, bool cond, lua_flightMode_t luaMode, int *idx) {
    if (cond) {
        lua_pushinteger(L, luaMode);
        lua_rawseti(L, -2, *idx);
        (*idx)++;
    }
}

/***
Get current active (flight) modes
@function getFlightModes
@treturn {int,...} Array of current (flight) modes, modes are represented by FM_* fields. 

*/
static int inavGetFlightModes(lua_State *L)
{
    lua_newtable(L);
    int idx = 1;
    pushFlightMode(L, FLIGHT_MODE(FAILSAFE_MODE), LUA_FM_FAILSAFE, &idx);
    pushFlightMode(L, FLIGHT_MODE(MANUAL_MODE),  LUA_FM_MANUAL, &idx);
    pushFlightMode(L, FLIGHT_MODE(NAV_RTH_MODE), LUA_FM_NAV_RTH, &idx);
    pushFlightMode(L, FLIGHT_MODE(NAV_POSHOLD_MODE), LUA_FM_NAV_POSHOLD, &idx);
    pushFlightMode(L, FLIGHT_MODE(NAV_COURSE_HOLD_MODE), LUA_FM_NAV_COURSE_HOLD, &idx);
    pushFlightMode(L, FLIGHT_MODE(NAV_COURSE_HOLD_MODE) && FLIGHT_MODE(NAV_ALTHOLD_MODE), LUA_FM_CRUISE, &idx);
    pushFlightMode(L, FLIGHT_MODE(NAV_ALTHOLD_MODE), LUA_FM_ALTHOLD, &idx);
    pushFlightMode(L, FLIGHT_MODE(ANGLE_MODE), LUA_FM_ANGLE, &idx);
    pushFlightMode(L, FLIGHT_MODE(HORIZON_MODE), LUA_FM_HORIZON, &idx);
    pushFlightMode(L, FLIGHT_MODE(AIRMODE_ACTIVE), LUA_FM_AIR, &idx);
    pushFlightMode(L, IS_RC_MODE_ACTIVE(BOXUSER1), LUA_FM_USER1, &idx);
    pushFlightMode(L, IS_RC_MODE_ACTIVE(BOXUSER2), LUA_FM_USER2, &idx);

    return 1;
}

/***
Get system uptime
@function getMillis
@treturn integer System uptime in milliseconds
*/
static int inavGetMillis(lua_State *L)
{
    lua_pushinteger(L, millis());
    return 1;
}

/***
Get RC channel value
@function getRcChannelValue
@tparam integer index Index of RC Channel (1 - 18)
@treturn integer Channel value in us, NIL if channel index is out of range
*/
static int inavGetRcChannelValue(lua_State *L)
{
    int idx = luaL_checkinteger(L, 1);
    if (idx < 1 || idx > MAX_SUPPORTED_RC_CHANNEL_COUNT) {
        lua_pushnil(L);
    } else {
        lua_pushinteger(L, rxGetChannelValue(idx - 1));
    }
    return 1;
}

/***
Re-maps a number from one range to another. That is, a value of fromLow would get mapped to toLow, a value of fromHigh to toHigh, values in-between to values in-between, etc.
Does not constrain values to within the range, because out-of-range values are sometimes intended and useful. 
The inav.constrain function may be used either before or after this function, if limits to the ranges are desired.
@function map
@tparam integer value The number to map
@tparam integer in_min The lower bound of the value’s current range.
@tparam integer in_max The upper bound of the value’s current range.
@tparam integer out_min The lower bound of the value’s target range.
@tparam integer out_max The upper bound of the value’s target range.
@treturn integer The mapped value
 */
static int inavMap(lua_State *L)
{
    lua_Integer value = luaL_checkinteger(L, 1);
    lua_Integer in_min = luaL_checkinteger(L, 2);
    lua_Integer in_max = luaL_checkinteger(L, 3);
    lua_Integer out_min = luaL_checkinteger(L, 4); 
    lua_Integer out_max = luaL_checkinteger(L, 5);

    lua_Integer ret = (value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    lua_pushinteger(L, ret);
    return 1;
}

/***
Constrains a number to be within a range.
@function constrain
@tparam number|integer value The number to constrain
@tparam number|integer low The lower end of the range
@tparam number|integer high The upper end of the range
@treturn number|integer Constrained number, NIL if parameters aren't integer or numbers
*/
static int inavConstrain(lua_State *L)
{
    if (lua_isinteger(L, 1))  {
        lua_Integer value = luaL_checkinteger(L, 1);
        lua_Integer low = luaL_checkinteger(L, 2);
        lua_Integer high = luaL_checkinteger(L, 3);
        lua_pushinteger(L, constrain(value, low, high));
    } else if (lua_isnumber(L, 1)) {
        lua_Number value = luaL_checknumber (L, 1);
        lua_Number low = luaL_checknumber(L, 2);
        lua_Number high = luaL_checknumber(L, 3);
        lua_pushnumber(L, constrainf(value, low, high));
    } else {
        lua_pop(L, lua_gettop(L));
        lua_pushnil(L);
    }
    return 1;
}

/***
Receives any number of arguments and prints their values to CLI (user_script_dbg command) and LOG, works like LUA's print (which is disabled)
@function dbgPrint
@param ... Any number of arguments to be printed
*/ 
static int inavDbgPrint(lua_State *L) {       
    int n = lua_gettop(L);  /* number of arguments */
    int i;
    for (i = 1; i <= n; i++) {  /* for each argument */
        size_t l;
        const char *s = luaL_tolstring(L, i, &l);  /* convert it to string */
        if (i > 1)  /* not the first element? */
            userScriptPuts("\t");  /* add a tab before it */
        userScriptPuts(s);  /* print it */
        lua_pop(L, 1);  /* pop result */
    }
    userScriptPuts("\n");
    return 0;
}

static const luaL_Reg inav_funcs[] = {
    {"getGvar", inavGetGvar},
    {"setGvar", inavSetGvar},
    {"overrideArmingSafety", inavOverrideArmingSafety},
    {"overrideThrottleScale", inavOverrideThrottleScale},
    {"swapRollYaw", inavSwapRollYaw},
    {"setVTXPowerLevel", inavSetVTXPowerLevel},
    {"setVTXBand", inavSetVTXBand},
    {"setVTXChannel", inavSetVTXChannel},
    {"invertYaw", inavInvertYaw},
    {"invertRoll", inavInvertRoll},
    {"invertPitch", inavInvertPitch},
    {"overrideThrottle", inavOverrideThrottle},
    {"setOSDLayout", inavSetOSDLayout},
    {"setPort", inavSetPort},
    {"rcChannelOverride", inavRcChannelOverride},
    {"setHeadingTarget", inavSetHeadingTarget}, 
    {"getFlightTime", inavGetFlightTime},
    {"getArmTime", inavGetArmTime},
    {"getTripDistance", inavGetTripDistance},
    {"getCellVoltage", inavGetCellVoltage},
    {"getDistanceToHome", inavGetDistanceToHome},
    {"getRssi", inavGetRssi},
    {"getCellCount", inavGetCellCount},
    {"getVbat", inavGetVbat},
    {"getCurrentAmperage", inavgGetCurrentAmperage},
    {"getCurrentDrawn", inavGetCurrentDrawn},
    {"getGpsSats", inavGetGpsSats},
    {"isGpsFix", inavIsGpsFix},
    {"getGroundSpeed", inavGetGroundSpeed},
    {"get3DSpeed", inavGet3DSpeed},
    {"getAirSpeed", inavGetAirSpeed},
    {"getFlightAltitude", inavGetFlightAltitude},
    {"getVerticalSpeed", inavGetVerticalSpeed},
    {"getFlightThrottlePos", inavGetFlightThrottlePos},
    {"getFlightAttitiudePitch", inavGetFlightAttitiudePitch},
    {"getFlightAttitiudeRoll", inavGetFlightAttitiudeRoll},
    {"isArmed", inavIsArmed},
    {"isAutolaunch", inavIsAutolaunch},
    {"isAltitudeControl", inavIsAltitudeControl},
    {"isPostionControl", inavIsPostionControl},
    {"isEmergecyLanding", inavIsEmergecyLanding},
    {"isRTH", inavIsRTH},
    {"isWaypoint", inavIsWaypoint},
    {"isLanding", inavIsLanding},
    {"isfailsafe", inavIsfailsafe},
    {"getPidOut", inavGetPidOut},
    {"getWaypointAction", inavGetWaypointAction},
    {"getWpIndex", inavGetWpIndex},
    {"get3dHomeDistance", inavGet3dHomeDistance},
    {"getCrsfLQ", inavGetCrsfLQ},
    {"getCrsfSNR", inavGetCrsfSNR},
    {"getFlightModes", inavGetFlightModes},
    {"getMillis", inavGetMillis},
    {"getRcChannelValue", inavGetRcChannelValue},
    {"map", inavMap},
    {"constrain", inavConstrain},
    {"dbgPrint", inavDbgPrint},
    {NULL, NULL}
};

LUALIB_API int luaopen_inav(lua_State *L)
{
    luaL_newlib(L, inav_funcs);

    /// @field yaw Yaw Axis
    lua_pushinteger(L, YAW);
    lua_setfield(L, -2, "yaw");

    /// @field roll Roll Axis
    lua_pushinteger(L, ROLL);
    lua_setfield(L, -2, "roll");

    /// @field pitch Pitch axis
    lua_pushinteger(L, PITCH);
    lua_setfield(L, -2, "pitch");

    /// @field WP_waypoint Waypoint action: Waypoint
    lua_pushinteger(L, NAV_WP_ACTION_WAYPOINT);
    lua_setfield(L, -2, "WP_waypoint");

    /// @field WP_holdTime Waypoint action: Hold time
    lua_pushinteger(L, NAV_WP_ACTION_HOLD_TIME);
    lua_setfield(L, -2, "WP_holdTime");

    /// @field WP_RTH Waypoint action: Return to home
    lua_pushinteger(L, NAV_WP_ACTION_RTH),
    lua_setfield(L, -2, "WP_RTH");
    
    /// @field WP_setPOI Waypoint action: Set POI
    lua_pushinteger(L, NAV_WP_ACTION_SET_POI);
    lua_setfield(L, -2, "WP_setPOI");
    
    /// @field WP_jump Waypoint action: Jump
    lua_pushinteger(L, NAV_WP_ACTION_JUMP);
    lua_setfield(L, -2, "WP_jump");
    
    /// @field WP_setHead Waypoint action: Set Heading
    lua_pushinteger(L, NAV_WP_ACTION_SET_HEAD);
    lua_setfield(L, -2, "WP_setHead");
    
    /// @field WP_Land Waypoint action: Land
    lua_pushinteger(L, NAV_WP_ACTION_LAND);
    lua_setfield(L, -2, "WP_Land");
    
    /// @field FM_failsafe Flight mode: Failsafe
    lua_pushinteger(L, LUA_FM_FAILSAFE);
    lua_setfield(L, -2, "FM_failsafe");
    
    /// @field FM_manual Flight mode: Manual
    lua_pushinteger(L, LUA_FM_MANUAL);
    lua_setfield(L, -2, "FM_manual");

    /// @field FM_NAV_RTH Flight mode: Return to home
    lua_pushinteger(L, LUA_FM_NAV_RTH);
    lua_setfield(L, -2, "FM_NAV_RTH");
    
    /// @field FM_NAV_poshold Flight mode: POsition hold
    lua_pushinteger(L, LUA_FM_NAV_POSHOLD);
    lua_setfield(L, -2, "FM_NAV_poshold");
    
    /// @field FM_NAV_courseHold: Flight mode: Course hold
    lua_pushinteger(L, LUA_FM_NAV_COURSE_HOLD);
    lua_setfield(L, -2, "FM_NAV_courseHold");
    
    /// @field FM_NAV_cruise Flight mode Cruise
    lua_pushinteger(L, LUA_FM_CRUISE);
    lua_setfield(L, -2, "FM_NAV_cruise");
    
    /// @field FM_NAV_althold Flight mode Altitude hold
    lua_pushinteger(L, LUA_FM_ALTHOLD);
    lua_setfield(L, -2, "FM_NAV_althold");
    
    /// @field FM_angle Flight mode: Angle
    lua_pushinteger(L, LUA_FM_ANGLE);
    lua_setfield(L, -2, "FM_angle");
    
    /// @field FM_horizon Flight mode: Horizon
    lua_pushinteger(L, LUA_FM_HORIZON);
    lua_setfield(L, -2, "FM_horizon");
    
    /// @field FM_air Flight mode: Air mode
    lua_pushinteger(L, LUA_FM_AIR);
    lua_setfield(L, -2, "FM_air");
    
    /// @field FM_user1 Flight mode: User1
    lua_pushinteger(L, LUA_FM_USER1);
    lua_setfield(L, -2, "FM_user1");
    
    /// @field FM_user2 Flight mode: User2
    lua_pushinteger(L, LUA_FM_USER2);
    lua_setfield(L, -2, "FM_user2");
    
    return 1;
}

#endif