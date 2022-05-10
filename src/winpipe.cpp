#include "winpipe.h"

#include <stdio.h>

const char* METATABLE_HANDLE = "winpipe.HANDLE";

static int lib_constants(lua_State *L) {
    lua_newtable(L);
    //addConstant(L, "", );
    // CreateNamedPipe:dwOpenMode, same for all
    addConstant(L, "PIPE_ACCESS_INBOUND", PIPE_ACCESS_INBOUND);
    addConstant(L, "PIPE_ACCESS_OUTBOUND", PIPE_ACCESS_OUTBOUND);
    addConstant(L, "PIPE_ACCESS_DUPLEX", PIPE_ACCESS_DUPLEX);
    // CreateNamedPipe:dwOpenMode, can differ
    addConstant(L, "FILE_FLAG_FIRST_PIPE_INSTANCE", FILE_FLAG_FIRST_PIPE_INSTANCE);
    addConstant(L, "FILE_FLAG_WRITE_THROUGH", FILE_FLAG_WRITE_THROUGH);
    addConstant(L, "FILE_FLAG_OVERLAPPED", FILE_FLAG_OVERLAPPED);
    addConstant(L, "WRITE_DAC", WRITE_DAC);
    addConstant(L, "WRITE_OWNER", WRITE_OWNER);
    addConstant(L, "ACCESS_SYSTEM_SECURITY", ACCESS_SYSTEM_SECURITY);
    // CreateNamedPipe:dwPipeMode, same for all
    addConstant(L, "PIPE_TYPE_BYTE", PIPE_TYPE_BYTE);
    addConstant(L, "PIPE_TYPE_MESSAGE", PIPE_TYPE_MESSAGE);
    // CreateNamedPipe:dwPipeMode, can differ
    addConstant(L, "PIPE_READMODE_BYTE", PIPE_READMODE_BYTE);
    addConstant(L, "PIPE_READMODE_MESSAGE", PIPE_READMODE_MESSAGE);
    addConstant(L, "PIPE_WAIT", PIPE_WAIT);
    addConstant(L, "PIPE_NOWAIT", PIPE_NOWAIT);
    addConstant(L, "PIPE_ACCEPT_REMOTE_CLIENTS", PIPE_ACCEPT_REMOTE_CLIENTS);
    addConstant(L, "PIPE_REJECT_REMOTE_CLIENTS", PIPE_REJECT_REMOTE_CLIENTS);
    
    return 1;
}

static int lib_mask(lua_State *L) {
    int top = lua_gettop(L);
    long long result = 0;
    for (int i = 1; i <= top; i++) {
        long long arg = luaL_checkinteger(L, i);
        result |= arg;
        printf("%lld\n", arg);
    }
    lua_pushnumber(L, result);
    return 1;
}

static int lib_CreateNamedPipe(lua_State *L) {
   // TODO: add __gc to handle metatable
   HANDLE* pHandle = (HANDLE*) lua_newuserdata(L, sizeof(HANDLE));
   luaL_getmetatable(L, METATABLE_HANDLE);
   lua_setmetatable(L, -2);
   
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
    HANDLE* pHandle = getHandle(L, 1);
    WINBOOL result = CloseHandle(*pHandle);
    lua_pushboolean(L, result);
    return 1;
}

static HANDLE* getHandle(lua_State *L, int index) {
    HANDLE* pHandle = (HANDLE*) luaL_checkudata(L, index, METATABLE_HANDLE);
    luaL_argcheck(L, pHandle != NULL, index, "HANDLE* expected");
    return pHandle;
}

static void addConstant(lua_State *L, const char* name, unsigned long value) {
    lua_pushstring(L, name);
    lua_pushnumber(L, value);
    lua_settable(L, -3);
}

static int pointerEquals(lua_State *L) {
    void* p1 = lua_touserdata(L, 1);
    void* p2 = lua_touserdata(L, 2);
    bool result = (p1 == p2);
    lua_pushboolean(L, result);
    return 1;
}

// DLL entry point
BOOL APIENTRY DllMain(HANDLE hModule, DWORD  fdwReason, LPVOID lpReserved) {
    return TRUE;
}

static const struct luaL_Reg library_functions[] = {
    {"winpipe_CreateNamedPipe", lib_CreateNamedPipe},
    {"winpipe_CloseHandle", lib_CloseHandle},
    {"winpipe_constants", lib_constants},
    {"winpipe_mask", lib_mask},
    {NULL, NULL}
};

extern "C" LUALIB_API int luaopen_winpipe(lua_State *L) {
    luaL_newmetatable(L, METATABLE_HANDLE);
    // set __eq to HANDLE
    lua_pushstring(L, "__eq");
    lua_pushcfunction(L, pointerEquals);
    lua_settable(L, -3);
    printf("%d", lua_gettop(L));

    luaL_newlib(L, library_functions);
    return 1;
}
