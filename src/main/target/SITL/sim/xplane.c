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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>
#include <math.h>

#include "platform.h"

#include "target.h"
#include "target/SITL/sim/xplane.h"
#include "target/SITL/sim/simHelper.h"
#include "fc/runtime_config.h"
#include "drivers/time.h"
#include "drivers/accgyro/accgyro_fake.h"
#include "drivers/barometer/barometer_fake.h"
#include "sensors/battery_sensor_fake.h"
#include "sensors/acceleration.h"
#include "drivers/pitotmeter/pitotmeter_fake.h"
#include "common/utils.h"
#include "common/maths.h"
#include "flight/mixer.h"
#include "flight/servos.h"
#include "flight/imu.h"
#include "io/gps.h"

#define XP_PORT 49000


static uint8_t pwmMapping[XP_MAX_PWM_OUTS];
static uint8_t mappingCount;

static struct sockaddr_in serverAddr;
static int sockFd;
static pthread_t listenThread;
static bool initalized = false;
static bool useImu = false;

static float lattitude = 0; 
static float longitude = 0;
static float elevation = 0;
static float local_vx = 0;
static float local_vy = 0;
static float local_vz = 0;
static float groundspeed = 0;
static float airspeed = 0;
static float roll = 0;
static float pitch = 0;
static float yaw = 0;
static float hpath = 0;
static float accel_x = 0;
static float accel_y = 0;
static float accel_z = 0;
static float gyro_x = 0;
static float gyro_y = 0;
static float gyro_z = 0;
static float barometer = 0;


typedef enum 
{
    DREF_LATITUDE,
    DREF_LONGITUDE,
    DREF_ELEVATION,
    DREF_LOCAL_VX,
    DREF_LOCAL_VY,
    DREF_LOCAL_VZ,
    DREF_GROUNDSPEED,
    DREF_TRUE_AIRSPEED,
    DREF_POS_PHI,
    DREF_POS_THETA,
    DREF_POS_PSI,
    DREF_POS_HPATH,
    DREF_FORCE_G_AXI1,
    DREF_FORCE_G_SIDE,
    DREF_FORCE_G_NRML,
    DREF_POS_P,
    DREF_POS_Q,
    DREF_POS_R,
    DREF_POS_BARO_CURRENT_INHG,
    DREF_COUNT
} dref_t;

uint32_t xint2uint32 (uint8_t * buf) 
{
	return buf[3] << 24 | buf [2] << 16 | buf [1] << 8 | buf [0];
}

float xflt2float (uint8_t * buf) 
{
	union {
		float f;
		uint32_t i;
	} v;

	v.i = xint2uint32 (buf);
	return v.f;
}

static void registerDref(dref_t id, char* dref, uint32_t freq)
{
    char buf[413];
    memset(buf, 0, sizeof(buf));

    strcpy(buf, "RREF");
    memcpy(buf + 5, &freq, 4);
    memcpy(buf + 9, &id, 4);
    memcpy(buf + 13, dref, strlen(dref) + 1);

    sendto(sockFd, (void*)buf, sizeof(buf), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
}

static void sendDref(char* dref, float value)
{
    char buf[509];
    strcpy(buf, "DREF");
	memcpy(buf + 5, &value, 4);
	memset(buf + 9, ' ', sizeof(buf) - 9);
	strcpy(buf + 9, dref);

    sendto(sockFd, (void*)buf, sizeof(buf), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
}

static void* listenWorker(void* arg)
{
    UNUSED(arg);

    uint8_t buf[1024];
    struct sockaddr remoteAddr;
    socklen_t slen = sizeof(remoteAddr);
    int recvLen;

    while (true)
    {
        
        float motorValue = 0;
        float yokeValues[3] = { 0 };
        int y = 0;
        for (int i = 0; i < mappingCount; i++) {
            if (y > 2) {
                break;
            }
            if (pwmMapping[i] & 0x80) { // Motor)
                motorValue = PWM_TO_FLOAT_0_1(motor[pwmMapping[i] & 0x7f]);
            } else {
                yokeValues[y] = PWM_TO_FLOAT_MINUS_1_1(servo[pwmMapping[i]]);
                y++;   
            }
        }
            
        sendDref("sim/operation/override/override_joystick", 1);
        sendDref("sim/cockpit2/engine/actuators/throttle_ratio_all", motorValue);
        sendDref("sim/joystick/yoke_roll_ratio", yokeValues[0]);
        sendDref("sim/joystick/yoke_pitch_ratio", yokeValues[1]);
        sendDref("sim/joystick/yoke_heading_ratio", yokeValues[2]);
        
        recvLen = recvfrom(sockFd, buf, sizeof(buf), 0, (struct sockaddr*)&remoteAddr, &slen);
        if (recvLen < 0 && errno != EWOULDBLOCK) {
            break;
        } 

        if (strncmp((char*)buf, "RREF", 4) != 0) {
            break;
        }

        for (int i = 5; i < recvLen; i += 8) {
            dref_t dref = (dref_t)xint2uint32(&buf[i]);
            float value = xflt2float(&(buf[i + 4]));
            
            switch (dref)
            {
                case DREF_LATITUDE:
                    lattitude = value;
                    break;

                case DREF_LONGITUDE:
                    longitude = value;
                    break;

                case DREF_ELEVATION:
                    elevation = value;
                    break;

                case DREF_LOCAL_VX:
                    local_vx = value;
                    break;

                case DREF_LOCAL_VY:
                    local_vy = value;
                    break;

                case DREF_LOCAL_VZ:
                    local_vz = value;
                    break;

                case DREF_GROUNDSPEED:
                    groundspeed = value;
                    break;

                case DREF_TRUE_AIRSPEED:
                    airspeed = value;
                    break;

                case DREF_POS_PHI:
                    roll = value;
                    break;

                case DREF_POS_THETA:
                    pitch = value;
                    break;

                case DREF_POS_PSI:
                    yaw = value;
                    break;

                case DREF_POS_HPATH:
                    hpath = value;
                    break;

                case DREF_FORCE_G_AXI1:
                    accel_x = value;
                    break;
            
                case DREF_FORCE_G_SIDE:
                    accel_y = value;
                    break;

                case DREF_FORCE_G_NRML:
                    accel_z = value;
                    break;

                case DREF_POS_P:
                    gyro_x = value;
                    break;

                case DREF_POS_Q:
                    gyro_y = value;
                    break;
                
                case DREF_POS_R:
                    gyro_z = value;
                    break;

                case DREF_POS_BARO_CURRENT_INHG:
                    barometer = value;
                    break;

                default:
                    break;
            }

        }

        if (hpath < 0) {
            hpath += 3600;
        }

        if (yaw < 0){
            yaw += 3600;
        }

        gpsFakeSet(
            GPS_FIX_3D,
            16,
            (int32_t)round(lattitude * 10000000),
            (int32_t)round(longitude * 10000000),
            (int32_t)round(elevation * 100),
            (int16_t)round(groundspeed * 100),
            (int16_t)round(hpath * 10),
            0, //(int16_t)round(-local_vz * 100),
            0, //(int16_t)round(local_vx * 100),
            0, //(int16_t)round(-local_vy * 100),
            0
        );

        if (!useImu) {
            imuSetAttitudeRPY(
                (int16_t)round(roll * 10), 
                (int16_t)round(-pitch * 10), 
                (int16_t)round(yaw * 10)
            );
            imuUpdateAttitude(micros());
        }
        
        fakeAccSet(
            clampToInt16(-accel_x * GRAVITY_MSS * 1000),
            clampToInt16(accel_y * GRAVITY_MSS * 1000),
            clampToInt16(accel_z * GRAVITY_MSS * 1000)
        );

        fakeGyroSet(
            clampToInt16(gyro_x * 16.0f),
            clampToInt16(-gyro_y * 16.0f),
            clampToInt16(-gyro_z * 16.0f)
        );

        fakeBaroSet((int32_t)round(barometer * 3386.39f), DEGREES_TO_CENTIDEGREES(21));
        fakePitotSetAirspeed(airspeed * 100.0f);

        fakeBattSensorSetVbat(16.8 * 100);

        if (!initalized) {
            ENABLE_ARMING_FLAG(SIMULATOR_MODE_SITL);                        
            initalized = true;
        }

        unlockMainPID();
    }

    return NULL;
}

bool simXPlaneInit(char* ip, int port, uint8_t* mapping, uint8_t mapCount, bool imu)
{
    memcpy(pwmMapping, mapping, mapCount);
    mappingCount = mapCount;
    useImu = imu;
    
    sockFd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sockFd < 0) {
        return false;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(0);

    struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;
	if (setsockopt(sockFd, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *) &tv,sizeof(struct timeval))) {
        return false;
    }

    if (bind(sockFd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        return false;
    }

    serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(ip);
	serverAddr.sin_port = htons(port);

    registerDref(DREF_LATITUDE, "sim/flightmodel/position/latitude", 100);
    registerDref(DREF_LONGITUDE, "sim/flightmodel/position/longitude", 100);
    registerDref(DREF_ELEVATION, "sim/flightmodel/position/elevation", 100);
    registerDref(DREF_LOCAL_VX, "sim/flightmodel/position/local_vx", 100);
    registerDref(DREF_LOCAL_VY, "sim/flightmodel/position/local_vy", 100);
    registerDref(DREF_LOCAL_VZ, "sim/flightmodel/position/local_vz", 100);
    registerDref(DREF_GROUNDSPEED, "sim/flightmodel/position/groundspeed", 100);
    registerDref(DREF_TRUE_AIRSPEED, "sim/flightmodel/position/true_airspeed", 100);
    registerDref(DREF_POS_PHI, "sim/flightmodel/position/phi", 100);
    registerDref(DREF_POS_THETA, "sim/flightmodel/position/theta", 100);
    registerDref(DREF_POS_PSI, "sim/flightmodel/position/psi", 100);
    registerDref(DREF_POS_HPATH, "sim/flightmodel/position/hpath", 100);
    registerDref(DREF_FORCE_G_AXI1, "sim/flightmodel/forces/g_axil", 100);
    registerDref(DREF_FORCE_G_SIDE, "sim/flightmodel/forces/g_side", 100);
    registerDref(DREF_FORCE_G_NRML, "sim/flightmodel/forces/g_nrml", 100);
    registerDref(DREF_POS_P, "sim/flightmodel/position/P", 100);
    registerDref(DREF_POS_Q, "sim/flightmodel/position/Q", 100);
    registerDref(DREF_POS_R, "sim/flightmodel/position/R", 100);
    registerDref(DREF_POS_BARO_CURRENT_INHG, "sim/weather/barometer_current_inhg", 100);

    if (pthread_create(&listenThread, NULL, listenWorker, NULL) < 0) {
        return false;
    }

    while(!initalized) {
        //
    }

    return true;

}