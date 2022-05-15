#include "waitnamedpipe.h"

#include <windows.h>

int lib_WaitNamedPipe(lua_State* L) {
    const char* pName = luaL_checkstring(L, 1);
    DWORD nTimeOut = luaL_checkinteger(L, 2);

    BOOL result = WaitNamedPipe(pName, nTimeOut);

    lua_pushboolean(L, result);
    return 1;
}
