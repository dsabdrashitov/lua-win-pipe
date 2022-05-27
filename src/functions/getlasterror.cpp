#include "getlasterror.h"

#include <windows.h>

namespace winpipe::functions {

int lib_GetLastError(lua_State* L) {
    DWORD result = GetLastError();

    lua_pushinteger(L, result);
    return 1;
}

}
