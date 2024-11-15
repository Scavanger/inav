/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>
#include <pthread.h>

#include "platform.h"

#include "common/axis.h"
#include "common/utils.h"

#include "fc/runtime_config.h"

#include "drivers/accgyro/accgyro.h"
#include "drivers/accgyro/accgyro_fake.h"


#ifdef USE_IMU_FAKE

#if defined(SITL_BUILD)

#define VOLATILE volatile

static pthread_mutex_t gyroMutex;
static pthread_mutex_t accMutex;

#define LOCK(mutex) (pthread_mutex_lock(mutex))
#define UNLOCK(mutex) (pthread_mutex_unlock(mutex))

#define GYROLOCK (pthread_mutex_lock(&gyroMutex))
#define GYROUNLOCK (pthread_mutex_unlock(&gyroMutex))
#define ACCLOCK (pthread_mutex_lock(&accMutex))
#define ACCUNLOCK (pthread_mutex_unlock(&accMutex))

#else
#define VOLATILE
#define GYROLOCK
#define GYROUNLOCK
#define ACCLOCK
#define ACCUNLOCK

#endif

static VOLATILE int16_t fakeGyroADC[XYZ_AXIS_COUNT];

static void fakeGyroInit(gyroDev_t *gyro)
{
    UNUSED(gyro);

#if defined(SITL_BUILD)
    pthread_mutex_init(&gyroMutex, NULL);
#endif

    //ENABLE_STATE(ACCELEROMETER_CALIBRATED);
}

void fakeGyroSet(int16_t x, int16_t y, int16_t z)
{
    GYROLOCK;
    fakeGyroADC[X] = x;
    fakeGyroADC[Y] = y;
    fakeGyroADC[Z] = z;
    GYROUNLOCK;
}

static bool fakeGyroRead(gyroDev_t *gyro)
{
    GYROLOCK;
    gyro->gyroADCRaw[X] = fakeGyroADC[X];
    gyro->gyroADCRaw[Y] = fakeGyroADC[Y];
    gyro->gyroADCRaw[Z] = fakeGyroADC[Z];
    GYROUNLOCK;
    return true;
}

static bool fakeGyroReadTemperature(gyroDev_t *gyro, int16_t *temperatureData)
{
    UNUSED(gyro);
    UNUSED(temperatureData);
    return true;
}

static bool fakeGyroInitStatus(gyroDev_t *gyro)
{
    UNUSED(gyro);
    return true;
}

bool fakeGyroDetect(gyroDev_t *gyro)
{
    gyro->initFn = fakeGyroInit;
    gyro->intStatusFn = fakeGyroInitStatus;
    gyro->readFn = fakeGyroRead;
    gyro->temperatureFn = fakeGyroReadTemperature;
    gyro->scale = 0.0625f;
    gyro->gyroAlign = 0;
    return true;
}

static VOLATILE int16_t fakeAccData[XYZ_AXIS_COUNT];

static void fakeAccInit(accDev_t *acc)
{
#if defined(SITL_BUILD)
    pthread_mutex_init(&accMutex, NULL);
#endif
    
    acc->acc_1G = 9806;
}

void fakeAccSet(int16_t x, int16_t y, int16_t z)
{ 
    ACCLOCK;
    fakeAccData[X] = x;
    fakeAccData[Y] = y;
    fakeAccData[Z] = z;
    ACCUNLOCK;
}

static bool fakeAccRead(accDev_t *acc)
{
    ACCLOCK;
    acc->ADCRaw[X] = fakeAccData[X];
    acc->ADCRaw[Y] = fakeAccData[Y];
    acc->ADCRaw[Z] = fakeAccData[Z];
    ACCUNLOCK;
    return true;
}

bool fakeAccDetect(accDev_t *acc)
{
    acc->initFn = fakeAccInit;
    acc->readFn = fakeAccRead;
    acc->accAlign = 0;
    return true;
}
#endif 

