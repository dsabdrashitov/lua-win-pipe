#include "readfile.h"

#include <windows.h>
#include "..\byteblock.h"
#include "..\bytebuffer.h"


int lib_ReadFile(lua_State* L) {
    HANDLE handle = *(winpipe::byteblock::getPHandle(L, 1));
    char* lpBuffer = lua_isnil(L, 2) ? NULL : getBuffer(L, 2);
    DWORD nBufferSize = luaL_checkinteger(L, 3);
    DWORD* lpBytesRead = lua_isnil(L, 4) ? NULL : winpipe::byteblock::getPDWORD(L, 4);
    luaL_argcheck(L, lua_isnil(L, 5), 5, "nil expected");
    
    BOOL result = ReadFile(handle, lpBuffer, nBufferSize, lpBytesRead, NULL);

    lua_pushboolean(L, result);
    return 1;
}
