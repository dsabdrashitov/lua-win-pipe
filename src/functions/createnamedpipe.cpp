#include "createnamedpipe.h"

#include <windows.h>
#include "..\byteblock.h"

namespace winpipe::functions {

int lib_CreateNamedPipe(lua_State* L) {   
    const char* pName = luaL_checkstring(L, 1);
    DWORD dwOpenMode = luaL_checkinteger(L, 2);
    DWORD dwPipeMode = luaL_checkinteger(L, 3);
    DWORD nMaxInstances = luaL_checkinteger(L, 4);
    DWORD nOutBufferSize = luaL_checkinteger(L, 5);
    DWORD nInBufferSize = luaL_checkinteger(L, 6);
    DWORD nTimeoutMs = luaL_checkinteger(L, 7);
    luaL_argcheck(L, lua_isnil(L, 8), 8, "nil expected");

    winpipe::byteblock::createByteBlock(L, sizeof(HANDLE));
    HANDLE* pHandle = winpipe::byteblock::getPHandle(L, -1);
    
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

}
