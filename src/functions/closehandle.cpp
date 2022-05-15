#include "closehandle.h"

#include <windows.h>
#include "..\phandle.h"


int lib_CloseHandle(lua_State* L) {
    HANDLE handle = *(getHandlePointer(L, 1));

    WINBOOL result = CloseHandle(handle);
    
    lua_pushboolean(L, result);
    return 1;
}
