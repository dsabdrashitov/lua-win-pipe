#include <windows.h>
 
// Lua marks for building as DLL
#define LUA_LIB
#define LUA_BUILD_AS_DLL
 
// Lua headers
extern "C" {
#include "include\lauxlib.h"
#include "include\lua.h"
}
 
// DLL entry point
BOOL APIENTRY DllMain(HANDLE hModule, DWORD  fdwReason, LPVOID lpReserved) {
   return TRUE;
}

static int l_hell(lua_State *L) {
    lua_pushstring(L, "hello");
    return 1;
}

static const struct luaL_Reg library_functions[] = {
    {"somefunc", l_hell},
    {NULL, NULL}
};

extern "C" LUALIB_API int luaopen_winpipe(lua_State *L) {
    luaL_newlib(L, library_functions);
    return 1;
}
