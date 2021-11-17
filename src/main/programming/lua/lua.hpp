// lua.hpp
// Lua header files for C++
// <<extern "C">> not supplied automatically because Lua also compiles as C++

#if defined(USE_SDCARD) && defined(USE_USER_SCRIPT)

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#endif