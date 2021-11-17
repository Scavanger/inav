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

#include "memory.h"
#include "common/log.h"
#include "common/umm_malloc/umm_malloc.h"
#include "common/umm_malloc/umm_malloc_cfg.h"
#include "fc/runtime_config.h"

static uint8_t dynamicHeap[DYNAMIC_HEAP_SIZE * 1024];
void* UMM_MALLOC_CFG_HEAP_ADDR = &dynamicHeap;
uint32_t UMM_MALLOC_CFG_HEAP_SIZE = DYNAMIC_HEAP_SIZE * 1024;

void memInit(void) 
{    
    umm_init();
}

void *memReallocate(void* mem, size_t wantedSize)
{
    void* ptr = umm_realloc(mem, wantedSize);
    if (!ptr) {
        // OOM
        LOG_E(SYSTEM, "Out of memory");
        ENABLE_ARMING_FLAG(ARMING_DISABLED_OOM);
    }
    return ptr;
}

void *memAllocate(size_t wantedSize)
{
    void* ptr = umm_malloc(wantedSize); 
    if (!ptr) {
        // OOM
        LOG_E(SYSTEM, "Out of memory");
        ENABLE_ARMING_FLAG(ARMING_DISABLED_OOM);
    }
    return ptr;
}

void memFree(void* ptr) 
{
    umm_free(ptr);
}

size_t memGetAvailableBytes(void) 
{
    return umm_free_heap_size();
}
