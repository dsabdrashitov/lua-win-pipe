#ifndef LUAWINPIPE_WINPIPE_H
#define LUAWINPIPE_WINPIPE_H

// Lua marks for building as DLL
#define LUA_LIB
#define LUA_BUILD_AS_DLL
 
// Lua headers
extern "C" {
    #include <lauxlib.h>
    #include <lua.h>
}

#include <windows.h>

static HANDLE getHandle(lua_State *L, int index);
static void addLongConstant(lua_State *L, const char* name, unsigned long value);
static void addPointerConstant(lua_State *L, const char* name, void* value, const char* metatable);
static int pointerEquals(lua_State *L);

#endif
