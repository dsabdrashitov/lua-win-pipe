#include "winpipe.h"

#include "metaphandle.h"
#include "constants.h"
#include "utils.h"
#include <windows.h>


static int lib_CreateNamedPipe(lua_State* L) {   
   const char* pName = luaL_checkstring(L, 1);
   DWORD dwOpenMode = luaL_checkinteger(L, 2);
   DWORD dwPipeMode = luaL_checkinteger(L, 3);
   DWORD nMaxInstances = luaL_checkinteger(L, 4);
   DWORD nOutBufferSize = luaL_checkinteger(L, 5);
   DWORD nInBufferSize = luaL_checkinteger(L, 6);
   DWORD nTimeoutMs = luaL_checkinteger(L, 7);
   luaL_argcheck(L, lua_isnil(L, 8), 8, "nil expected");

   HANDLE* pHandle = createHandlePointer(L);
   
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

static int lib_ConnectNamedPipe(lua_State* L) {
    HANDLE handle = *(getHandlePointer(L, 1));
    luaL_argcheck(L, lua_isnil(L, 2), 2, "nil expected");

    BOOL result = ConnectNamedPipe(handle, NULL);

    lua_pushboolean(L, result);
    return 1;
}

static int lib_CloseHandle(lua_State* L) {
    HANDLE handle = *(getHandlePointer(L, 1));

    WINBOOL result = CloseHandle(handle);
    
    lua_pushboolean(L, result);
    return 1;
}

// DLL entry point
BOOL APIENTRY DllMain(HANDLE hModule, DWORD  fdwReason, LPVOID lpReserved) {
    return TRUE;
}

static const struct luaL_Reg library_functions[] = {
    {"winpipe_CreateNamedPipe", lib_CreateNamedPipe},
    {"winpipe_ConnectNamedPipe", lib_ConnectNamedPipe},
    {"winpipe_CloseHandle", lib_CloseHandle},
    {"winpipe_constants", lib_constants},
    {"winpipe_mask", lib_mask},
    {NULL, NULL}
};

extern "C" LUALIB_API int luaopen_winpipe(lua_State* L) {
    registerMetaPHandle(L);
    luaL_newlib(L, library_functions);
    return 1;
}
