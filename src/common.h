#ifndef LUAWINPIPE_COMMON_H
#define LUAWINPIPE_COMMON_H

// Lua marks for building as DLL
#define LUA_LIB
#define LUA_BUILD_AS_DLL
 
// Lua headers
extern "C" {
    #include <lauxlib.h>
    #include <lua.h>
}

#endif
