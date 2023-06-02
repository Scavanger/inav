#pragma once

#include "drivers/osd.h"

#define FRSKY_DISPLAYPORT_TYPE "FrSky PixelOSD"

typedef struct displayPort_s displayPort_t;

displayPort_t *frskyOSDDisplayPortInit(const videoSystem_e videoSystem);
