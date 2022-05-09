#include <windows.h>
#include <stdio.h>
 
// Lua marks for building as DLL
#define LUA_LIB
#define LUA_BUILD_AS_DLL
 
// Lua headers
extern "C" {
#include <lauxlib.h>
#include <lua.h>
}

static void add_constant(lua_State *L, const char* name, unsigned long value) {
    lua_pushstring(L, name);
    lua_pushnumber(L, value);
    lua_settable(L, -3);
}

static int lib_constants(lua_State *L) {
    lua_newtable(L);
    //add_constant(L, "", );
    // CreateNamedPipe:dwOpenMode, same for all
    add_constant(L, "PIPE_ACCESS_INBOUND", PIPE_ACCESS_INBOUND);
    add_constant(L, "PIPE_ACCESS_OUTBOUND", PIPE_ACCESS_OUTBOUND);
    add_constant(L, "PIPE_ACCESS_DUPLEX", PIPE_ACCESS_DUPLEX);
    // CreateNamedPipe:dwOpenMode, can differ
    add_constant(L, "FILE_FLAG_FIRST_PIPE_INSTANCE", FILE_FLAG_FIRST_PIPE_INSTANCE);
    add_constant(L, "FILE_FLAG_WRITE_THROUGH", FILE_FLAG_WRITE_THROUGH);
    add_constant(L, "FILE_FLAG_OVERLAPPED", FILE_FLAG_OVERLAPPED);
    add_constant(L, "WRITE_DAC", WRITE_DAC);
    add_constant(L, "WRITE_OWNER", WRITE_OWNER);
    add_constant(L, "ACCESS_SYSTEM_SECURITY", ACCESS_SYSTEM_SECURITY);
    // CreateNamedPipe:dwPipeMode, same for all
    add_constant(L, "PIPE_TYPE_BYTE", PIPE_TYPE_BYTE);
    add_constant(L, "PIPE_TYPE_MESSAGE", PIPE_TYPE_MESSAGE);
    // CreateNamedPipe:dwPipeMode, can differ
    add_constant(L, "PIPE_READMODE_BYTE", PIPE_READMODE_BYTE);
    add_constant(L, "PIPE_READMODE_MESSAGE", PIPE_READMODE_MESSAGE);
    add_constant(L, "PIPE_WAIT", PIPE_WAIT);
    add_constant(L, "PIPE_NOWAIT", PIPE_NOWAIT);
    add_constant(L, "PIPE_ACCEPT_REMOTE_CLIENTS", PIPE_ACCEPT_REMOTE_CLIENTS);
    add_constant(L, "PIPE_REJECT_REMOTE_CLIENTS", PIPE_REJECT_REMOTE_CLIENTS);
    
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
   
   //TODO: push result to stack
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
    {"winpipe_CreateNamedPipe", lib_CreateNamedPipe},
    {"winpipe_CloseHandle", lib_CloseHandle},
    {"winpipe_constants", lib_constants},
    {"winpipe_mask", lib_mask},
    {NULL, NULL}
};

extern "C" LUALIB_API int luaopen_winpipe(lua_State *L) {
    luaL_newlib(L, library_functions);
    return 1;
}
