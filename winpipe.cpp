#include <windows.h>
 
// Lua marks for building as DLL
#define LUA_LIB
#define LUA_BUILD_AS_DLL
 
// Lua headers
extern "C" {
#include "include\lauxlib.h"
#include "include\lua.h"
}

static int l_hell(lua_State *L) {
   lua_pushstring(L, "hello");
   return 1;
}

static int lib_CreateNamedPipe(lua_State *L) {
   // TODO: add __gc to handle metatable
   HANDLE* pHandle = (HANDLE*) lua_newuserdata(L, sizeof(HANDLE));
   
   // get and encode 1 argument
   const char* pName = luaL_checkstring(L, 1);
   DWORD dwOpenMode = luaL_checkinteger(L, 2);
   DWORD dwPipeMode = luaL_checkinteger(L, 3);
   DWORD nMaxInstances = luaL_checkinteger(L, 4);
   DWORD nOutBufferSize = luaL_checkinteger(L, 5);
   DWORD nInBufferSize = luaL_checkinteger(L, 6);
   DWORD nTimeoutMs = luaL_checkinteger(L, 7);

   *pHandle = CreateNamedPipe(
         pName,
         dwOpenMode,
         dwPipeMode,
         nMaxInstances,
         nOutBufferSize,
         nInBufferSize,
         nTimeoutMs,
         NULL);
   
   return 1;
}

static int lib_CloseHandle(lua_State *L) {
   HANDLE* pHandle = (HANDLE*) lua_touserdata(L, 1);
   WINBOOL result = CloseHandle(*pHandle);
   lua_pushboolean(L, result);
   return 1;
}

// DLL entry point
BOOL APIENTRY DllMain(HANDLE hModule, DWORD  fdwReason, LPVOID lpReserved) {
   return TRUE;
}

static const struct luaL_Reg library_functions[] = {
    {"somefunc", l_hell},
    {"CreateNamedPipe", lib_CreateNamedPipe},
    {"CloseHandle", lib_CloseHandle},
    {NULL, NULL}
};

extern "C" LUALIB_API int luaopen_winpipe(lua_State *L) {
    luaL_newlib(L, library_functions);
    return 1;
}
