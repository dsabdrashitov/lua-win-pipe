#include "readfile.h"

#include <windows.h>
#include "..\phandle.h"
#include "..\bytebuffer.h"
#include "..\pdword.h"


int lib_ReadFile(lua_State* L) {
    HANDLE handle = *(getHandlePointer(L, 1));
    char* lpBuffer = lua_isnil(L, 2) ? NULL : getBuffer(L, 2);
    DWORD nBufferSize = luaL_checkinteger(L, 3);
    DWORD* lpBytesRead = lua_isnil(L, 4) ? NULL : getPDWORD(L, 4);
    luaL_argcheck(L, lua_isnil(L, 5), 5, "nil expected");
    
    BOOL result = ReadFile(handle, lpBuffer, nBufferSize, lpBytesRead, NULL);

    lua_pushboolean(L, result);
    return 1;
}
