#include "closehandle.h"

#include <windows.h>
#include "..\byteblock.h"


int lib_CloseHandle(lua_State* L) {
    HANDLE handle = *winpipe::byteblock::getPHandle(L, 1);

    WINBOOL result = CloseHandle(handle);
    
    lua_pushboolean(L, result);
    return 1;
}
