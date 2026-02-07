#include "waitnamedpipe.h"

#include <windows.h>

namespace winpipe::functions {

int lib_WaitNamedPipe(lua_State* L) {
    const char* pName = luaL_checkstring(L, 1);
    DWORD nTimeOut = luaL_checkinteger(L, 2);

    BOOL result = WaitNamedPipe(pName, nTimeOut);
    winpipe::g_LastStoredError = GetLastError();

    lua_pushboolean(L, result);
    return 1;
}

}
