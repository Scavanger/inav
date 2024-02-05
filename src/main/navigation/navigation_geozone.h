/*
 * This file is part of INAV.
 *
 * INAV is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * INAV is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with INAV. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "common/time.h"
#include "config/parameter_group.h"

#define MAX_GEOZONES_IN_CONFIG 63
#define MAX_VERTICES_IN_CONFIG 126

typedef enum {
    GEOZONE_MESSAGE_STATE_NONE,
    GEOZONE_MESSAGE_STATE_NFZ,
    GEOZONE_MESSAGE_STATE_LEAVING_FZ,
    GEOZONE_MESSAGE_STATE_OUTSIDE_FZ,
    GEOZONE_MESSAGE_STATE_ENTERING_NFZ,
    GEOZONE_MESSAGE_STATE_AVOIDING_FB,
    GEOZONE_MESSAGE_STATE_RETURN_TO_ZONE,
    GEOZONE_MESSAGE_STATE_FLYOUT_NFZ,
    GEOZONE_MESSAGE_STATE_AVOIDING_ALTITUDE_BREACH,
    GEOZONE_MESSAGE_STATE_LOITER
} geozoneMessageState_e;

enum fenceAction_e {
    FENCE_ACTION_NONE,
    FENCE_ACTION_AVOID,
    FENCE_ACTION_POS_HOLD,
    FENCE_ACTION_RTH,
};

enum noWayHomeAction {
    NO_WAY_HOME_ACTION_RTH,
    NO_WAY_HOME_ACTION_EMRG_LAND,
};

#define GEOZONE_SHAPE_CIRCULAR 0
#define GEOZONE_SHAPE_POLYGON  1

#define GEOZONE_TYPE_EXCLUSIVE 0
#define GEOZONE_TYPE_INCLUSIVE 1

typedef struct geoZoneConfig_s
{
    uint8_t shape;
    uint8_t type;
    int32_t minAltitude;
    int32_t maxAltitude;
    uint8_t fenceAction;
    uint8_t vertexCount;
} geoZoneConfig_t;

typedef struct geozone_config_s
{
    uint32_t fenceDetectionDistance;
    uint16_t avoidAltitudeRange;
    uint16_t safeAltitudeDistance;
    bool nearestSafeHomeAsInclusivZone;
    uint8_t safeHomeFenceAction;
    uint32_t copterFenceStopDistance;
    uint8_t noWayHomeAction;
} geozone_config_t;

typedef struct vertexConfig_s
{
    int8_t zoneId;
    uint8_t idx;
    int32_t lat;
    int32_t lon;
} vertexConfig_t;

PG_DECLARE(geozone_config_t, geoZoneConfig);
PG_DECLARE_ARRAY(geoZoneConfig_t, MAX_GEOZONES_IN_CONFIG, geoZonesConfig);
PG_DECLARE_ARRAY(vertexConfig_t, MAX_VERTICES_IN_CONFIG, geoZoneVertices);

typedef struct geozone_s {
    bool insideFz;
    bool insideNfz;
    uint32_t distanceToZoneBorder3d;
    int32_t vertDistanceToZoneBorder;
    geozoneMessageState_e messageState;
    int32_t directionToNearestZone;
    int32_t distanceHorToNearestZone;
    int32_t distanceVertToNearestZone;
    int32_t zoneInfo;
    int32_t currentzoneMaxAltitude; 
    int32_t currentzoneMinAltitude;
    bool sticksLocked;
    int8_t loiterDir;
    bool avoidInRTHInProgress;
    int32_t maxHomeAltitude;
    bool homeHasMaxAltitue;
} geozone_t;

extern geozone_t geozone;

void geozoneReset(void);
bool isGeozoneActive(void);
uint8_t geozoneGetUsedVerticesCount(void);
void geozoneResetVertices(int8_t zoneId, int16_t idx);
void geozoneUpdate(timeUs_t curentTimeUs);
bool geozoneIsInsideNFZ(void);
void geozoneAdvanceRthAvoidWaypoint(void);
int8_t geozoneCheckForNFZAtCourse(bool isRTH);
bool geoZoneIsLastRthWaypoint(void);
fpVector3_t *geozoneGetCurrentRthAvoidWaypoint(void);
void geozoneSetupRTH(void);
void geozoneResetRTH(void);
void geozoneUpdateMaxHomeAltitude(void);