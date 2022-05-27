#include "writefile.h"

#include <windows.h>
#include "..\byteblock.h"
#include "..\bytebuffer.h"


int lib_WriteFile(lua_State* L) {
    HANDLE handle = *(winpipe::byteblock::getPHandle(L, 1));
    char* lpBuffer = lua_isnil(L, 2) ? NULL : getBuffer(L, 2);
    DWORD nNumberOfBytesToWrite = luaL_checkinteger(L, 3);
    DWORD* lpBytesWritten = lua_isnil(L, 4) ? NULL : winpipe::byteblock::getPDWORD(L, 4);
    luaL_argcheck(L, lua_isnil(L, 5), 5, "nil expected");
    
    BOOL result = WriteFile(handle, lpBuffer, nNumberOfBytesToWrite, lpBytesWritten, NULL);

    lua_pushboolean(L, result);
    return 1;
}
