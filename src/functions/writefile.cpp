#include "writefile.h"

#include <windows.h>
#include "..\phandle.h"
#include "..\bytebuffer.h"
#include "..\pdword.h"


int lib_WriteFile(lua_State* L) {
    HANDLE handle = *(getHandlePointer(L, 1));
    char* lpBuffer = getBuffer(L, 2);
    DWORD nNumberOfBytesToWrite = luaL_checkinteger(L, 3);
    DWORD* lpBytesWritten = getPDWORD(L, 4);
    luaL_argcheck(L, lua_isnil(L, 5), 5, "nil expected");
    
    BOOL result = WriteFile(handle, lpBuffer, nNumberOfBytesToWrite, lpBytesWritten, NULL);

    lua_pushboolean(L, result);
    return 1;
}
