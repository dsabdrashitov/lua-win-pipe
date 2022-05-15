#include "connectnamedpipe.h"

#include <windows.h>
#include "..\phandle.h"

int lib_ConnectNamedPipe(lua_State* L) {
    HANDLE handle = *(getHandlePointer(L, 1));
    luaL_argcheck(L, lua_isnil(L, 2), 2, "nil expected");

    BOOL result = ConnectNamedPipe(handle, NULL);

    lua_pushboolean(L, result);
    return 1;
}
