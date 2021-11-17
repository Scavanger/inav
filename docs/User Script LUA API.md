# iNav LUA Api

Documentaion of the iNav LUA API.

- [Functions](#functions)

Name | Summary
--- | ---
  [setGvar](#setgvar-index-value) | Get GVAR (global variable) value
  [setGvar](#setgvar-index-value) | Set GVAR (global variable) value
  [overrideThrotteScale](#overridethrottescale-throttle) | Override throttle scale
  [overrideArmingSafety](#overridearmingsafety-) | Override arming saftey, allows to arm on any angle even without GPS fix
  [swapRollYaw](#swaprollyaw-) | Swap roll and yaw, basically, when activated, yaw stick will control roll and roll stick will control yaw.
  [setVTXPowerLevel](#setvtxpowerlevel-index) | Sets VTX power level
  [setVTXBand](#setvtxband-index) | Sets VTX band.
  [setVTXChannel](#setvtxchannel-index) | Sets VTX channel.
  [invertRoll](#invertroll-) | Inverts ROLL axis input for PID/PIFF controller
  [invertYaw](#invertyaw-) | Inverts YAW axis input for PID/PIFF controller
  [invertPitch](#invertpitch-) | Inverts PITCH axis input for PID/PIFF controller
  [overrideThrottle](#overridethrottle-value) | Override throttle value that is feed to the motors by mixer
  [setOSDLayout](#setosdlayout-index) | Sets OSD layout
  [portSet](#portset-pin-value) | Set I2C IO Expander
  [rcChannelOverride](#rcchanneloverride-channel-value) | Overrides an RC channel
  [setHeadingTarget](#setheadingtarget-degree) | Sets heading-hold target
  [getFlightTime](#getflighttime-) | Get flight time
  [getArmTime](#getarmtime-) | Get arm time
  [getDistanceToHome](#getdistancetohome-) | Get distance to home
  [getTripDistance](#gettripdistance-) | Get total travel distance
  [getRssi](#getrssi-) | Get Rssi
  [getVbat](#getvbat-) | Get battery voltage (VBat)
  [getCellVoltage](#getcellvoltage-) | Get cell voltage
  [getCellCount](#getcellcount-) | Get cell count
  [getCurrentAmperage](#getcurrentamperage-) | Get current amperage
  [getCurrentDrawn](#getcurrentdrawn-) | Get Current drawn
  [getGpsSats](#getgpssats-) | Get number of GPS sattelites
  [getGpsFix](#getgpsfix-) | Get Status of GPS fix
  [getGroundSpeed](#getgroundspeed-) | Gets speed over ground
  [get3DSpeed](#get3dspeed-) | Get 3D speed
  [getAirSpeed](#getairspeed-) | Get air speed
  [getFlightAltitude](#getflightaltitude-) | Get flight altitude
  [getVerticalSpeed](#getverticalspeed-) | Get vertical speed
  [getFlightThrottlePos](#getflightthrottlepos-) | Get flight throttle position
  [getFlightAttitiudePitch](#getflightattitiudepitch-) | Get flight attitude of pitch axis
  [getFlightAttitiudeRoll](#getflightattitiuderoll-) | Get flight attitude of roll axis
  [isArmed](#isarmed-) | Get arm status
  [isAutolaunch](#isautolaunch-) | Get autolaunch status
  [isAltitudeControl](#isaltitudecontrol-) | Get altitude control status
  [isPostionControl](#ispostioncontrol-) | Get position control status
  [isEmergecyLanding](#isemergecylanding-) | Get emergency landing status
  [isRTH](#isrth-) | Get return to home status
  [isWaypoint](#iswaypoint-) | Get waypoint status
  [isLanding](#islanding-) | Get landing status
  [isfailsafe](#isfailsafe-) | Get failsafe status
  [getPidOut](#getpidout-axis) | Get output of PID controller of selected axis
  [getWaypointAction](#getwaypointaction-) | Get waypoint action
  [getWpIndex](#getwpindex-) | Get index of current waypoint
  [get3dHomeDistance](#get3dhomedistance-) | Get 3D home distance
  [getCrsfLQ](#getcrsflq-) | Get Crossfire LQ
  [getCrsfSNR](#getcrsfsnr-) | Get Crossfire SNR
  [getFlightModes](#getflightmodes-) | Get current active (flight) modes
  [getMillis](#getmillis-) | Get system uptime
  [map](#map-value-in_min-in_max-out_min-out_max) | Re-maps a number from one range to another.
  [constrain](#constrain-value-low-high) | Constrains a number to be within a range.
  [dbgPrint](#dbgprint-...) | Receives any number of arguments and prints their values to CLI (user_script_dbg command) and LOG, works like LUA's print (which is disabled)
- [Fields](#fields)

Name | Summary
--- | ---
  [yaw](#yaw) |
  [roll](#roll) |
  [pitch](#pitch) |
  [WP_waypoint](#wp_waypoint) |
  [WP_holdTime](#wp_holdtime) |
  [WP_RTH](#wp_rth) |
  [WP_setPOI](#wp_setpoi) |
  [WP_jump](#wp_jump) |
  [WP_setHead](#wp_sethead) |
  [WP_Land](#wp_land) |
  [FM_failsafe](#fm_failsafe) |
  [FM_manual](#fm_manual) |
  [FM_NAV_RTH](#fm_nav_rth) |
  [FM_NAV_poshold](#fm_nav_poshold) |
  [FM_NAV_courseHold:](#fm_nav_coursehold:) |
  [FM_NAV_cruise](#fm_nav_cruise) |
  [FM_NAV_althold](#fm_nav_althold) |
  [FM_angle](#fm_angle) |
  [FM_horizon](#fm_horizon) |
  [FM_air](#fm_air) |
  [FM_user1](#fm_user1) |
  [FM_user2](#fm_user2) |



## Functions

### setGvar (Index, Value)
Get GVAR (global variable) value

**Parameters**
- Index: (*integer*)  of GVAR
- Value: (*integer*)  of GVAR

### setGvar (Index, Value)
Set GVAR (global variable) value

**Parameters**
- Index: (*integer*)  of GVAR to be set
- Value: (*integer*)  of GVAR

### overrideThrotteScale (Throttle)
Override throttle scale

**Parameters**
- Throttle: (*integer*)  scale in percent (value 0 - 100)

### overrideArmingSafety ()
Override arming saftey, allows to arm on any angle even without GPS fix

### swapRollYaw ()
Swap roll and yaw, basically, when activated, yaw stick will control roll and roll stick will control yaw.
Required for tail-sitters VTOL during vertical-horizonral transition when body frame changes.

### setVTXPowerLevel (Index)
Sets VTX power level

**Parameters**
- Index: (*integer*)  of powerlevel, values are 1-5 for SmartAudio and Tramp protocol

### setVTXBand (Index)
Sets VTX band.

**Parameters**
- Index: (*integer*)  of band, values are 1-5

### setVTXChannel (Index)
Sets VTX channel.

**Parameters**
- Index: (*integer*)  of channel, values are 1-8

### invertRoll ()
Inverts ROLL axis input for PID/PIFF controller

### invertYaw ()
Inverts YAW axis input for PID/PIFF controller

### invertPitch ()
Inverts PITCH axis input for PID/PIFF controller

### overrideThrottle (value)
Override throttle value that is feed to the motors by mixer

**Parameters**
- value: (*integer*)  New value in us, 1000 means throttle cut, 1500 means half throttle

### setOSDLayout (index)
Sets OSD layout

**Parameters**
- index: (*integer*)  Index of selected OSD layout, accepted values are 0-3

### portSet (pin, value)
Set I2C IO Expander

**Parameters**
- pin: (*integer*)  Pin, accepted values are 0 - 7
- value: (*bool*)  Pin value

### rcChannelOverride (channel, value)
Overrides an RC channel

**Parameters**
- channel: (*integer*)  Index of channel, accepted values are 1 - 18
- value: (*integer*)  Value of chennel in us, accepted values are 1000 - 2000

### setHeadingTarget (degree)
Sets heading-hold target

**Parameters**
- degree: (*integer*)  New target in degrees. Value wraps-around.

### getFlightTime ()
Get flight time

**Returns**

(*number*) Flight time in seconds

### getArmTime ()
Get arm time

**Returns**

(*number*) Arm time in seconds

### getDistanceToHome ()
Get distance to home

**Returns**

(*integer*) Distance to home in meters

### getTripDistance ()
Get total travel distance

**Returns**

(*integer*) Total travel distance in meters

### getRssi ()
Get Rssi

**Returns**

(*integer*) Rssi in percent

### getVbat ()
Get battery voltage (VBat)

**Returns**

(*integer*) VBat in volts * 100 (eg. 12.1 V is 1210)

### getCellVoltage ()
Get cell voltage

**Returns**

(*integer*) Average voltage per cell * 100 (e.g. 3.1V is 310)

### getCellCount ()
Get cell count

**Returns**

(*integer*) Number of battery cells

### getCurrentAmperage ()
Get current amperage

**Returns**

(*integer*) Current amperage * 100 (e.g. 23 A is 2300)

### getCurrentDrawn ()
Get Current drawn

**Returns**

(*integerege*) rCurrent drawn in mAh

### getGpsSats ()
Get number of GPS sattelites

**Returns**

(*integer*) Number of GPS sattelites

### getGpsFix ()
Get Status of GPS fix

**Returns**

(*bool*) TRUE if GPS has fix

### getGroundSpeed ()
Gets speed over ground

**Returns**

(*integer*) Speed pver ground in cm/s

### get3DSpeed ()
Get 3D speed

**Returns**

(*integer*) Speed over ground in cm/s

### getAirSpeed ()
Get air speed

**Returns**

(*integer*) Air speed in cm/s

### getFlightAltitude ()
Get flight altitude

**Returns**

(*integer*) Flight altitude in cm

### getVerticalSpeed ()
Get vertical speed

**Returns**

(*integer*) Vertical speed im cm/s

### getFlightThrottlePos ()
Get flight throttle position

**Returns**

(*integer*) Throttle position in %

### getFlightAttitiudePitch ()
Get flight attitude of pitch axis

**Returns**

(*integer*) Roll attitude in degrees

### getFlightAttitiudeRoll ()
Get flight attitude of roll axis

**Returns**

(*integer*) Roll attitude in degrees

### isArmed ()
Get arm status

**Returns**

(*bool*) TRUE if aircraft is armed

### isAutolaunch ()
Get autolaunch status

**Returns**

(*bool*) TRUE if autolaunch is active

### isAltitudeControl ()
Get altitude control status

**Returns**

(*bool*) TRUE if altitude control is active

### isPostionControl ()
Get position control status

**Returns**

(*bool*) TRUE if position control is active

### isEmergecyLanding ()
Get emergency landing status

**Returns**

(*bool*) TRUE if emergency landing is active

### isRTH ()
Get return to home status

**Returns**

(*bool*) TRUE if return to home is active

### isWaypoint ()
Get waypoint status

**Returns**

(*bool*) TRUE if waypoint mode is active

### isLanding ()
Get landing status

**Returns**

(*bool*) TRUE if landing is active

### isfailsafe ()
Get failsafe status

**Returns**

(*bool*) TRUE if failsafe is active

### getPidOut (axis)
Get output of PID controller of selected axis

**Parameters**
- axis: (*integer*) , Use fields yaw, pitch or roll

**Returns**

(*integer*) Pid Output (-500 - 500)

### getWaypointAction ()
Get waypoint action

**Returns**

(*integer*) One of WP_* fields

### getWpIndex ()
Get index of current waypoint

**Returns**

(*integer*) Index of current waypoint, starts with 1

### get3dHomeDistance ()
Get 3D home distance

**Returns**

(*number*) Distance to home (3D) im meter

### getCrsfLQ ()
Get Crossfire LQ

**Returns**

(*int*) Crossfire LQ

### getCrsfSNR ()
Get Crossfire SNR

**Returns**

(*number*) Crossfire SNR

### getFlightModes ()
Get current active (flight) modes

**Returns**

(*{int,...}*) Array of current (flight) modes, modes are represented by FM_* fields.

### getMillis ()
Get system uptime

**Returns**

(*integer*) System uptime ein milliseconds

### map (value, in_min, in_max, out_min, out_max)
Re-maps a number from one range to another.  That is, a value of fromLow would get mapped to toLow, a value of fromHigh to toHigh, values in-between to values in-between, etc.
Does not constrain values to within the range, because out-of-range values are sometimes intended and useful.
The inav.constrain function may be used either before or after this function, if limits to the ranges are desired.

**Parameters**
- value: (*integer*)  The number to map
- in_min: (*integer*)  The lower bound of the value’s current range.
- in_max: (*integer*)  The upper bound of the value’s current range.
- out_min: (*integer*)  The lower bound of the value’s target range.
- out_max: (*integer*)  The upper bound of the value’s target range.

**Returns**

(*integer*) The mapped value

### constrain (value, low, high)
Constrains a number to be within a range.

**Parameters**
- value: (*number|integer*)  The number to constrain
- low: (*number|integer*)  The lower end of the range
- high: (*number|integer*)  The upper end of the range

**Returns**

(*number|integer*) Constrained number, NIL if paramters aren't integer or numbers

### dbgPrint (...)
Receives any number of arguments and prints their values to CLI (user_script_dbg command) and LOG, works like LUA's print (which is disabled)

**Parameters**
- ...:   Any number of arguments to be printed


## Fields

### yaw

- yaw:   Yaw Axis

### roll

- roll:   Roll Axis

### pitch

- pitch:   Pitch axis

### WP_waypoint

- WP_waypoint:   Waypoint action: Waypoint

### WP_holdTime

- WP_holdTime:   Waypoint action: Hold time

### WP_RTH

- WP_RTH:   Waypoint action: Return to home

### WP_setPOI

- WP_setPOI:   Waypoint action: Set POI

### WP_jump

- WP_jump:   Waypoint action: Jump

### WP_setHead

- WP_setHead:   Waypoint action: Set Heading

### WP_Land

- WP_Land:   Waypoint action: Land

### FM_failsafe

- FM_failsafe:   Flight mode: Failsafe

### FM_manual

- FM_manual:   Flight mode: Manual

### FM_NAV_RTH

- FM_NAV_RTH:   Flight mode: Return to home

### FM_NAV_poshold

- FM_NAV_poshold:   Flight mode: POsition hold

### FM_NAV_courseHold:

- FM_NAV_courseHold::   Flight mode: Course hold

### FM_NAV_cruise

- FM_NAV_cruise:   Flight mode Cruise

### FM_NAV_althold

- FM_NAV_althold:   Flight mode Altitude hold

### FM_angle

- FM_angle:   Flight mode: Angle

### FM_horizon

- FM_horizon:   Flight mode: Horizon

### FM_air

- FM_air:   Flight mode: Air mode

### FM_user1

- FM_user1:   Flight mode: User1

### FM_user2

- FM_user2:   Flight mode: User2





