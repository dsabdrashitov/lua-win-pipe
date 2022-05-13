#include "peeknamedpipe.h"

#include <windows.h>
#include "..\phandle.h"
#include "..\bytebuffer.h"
#include "..\pdword.h"


int lib_PeekNamedPipe(lua_State* L) {
    HANDLE handle = *(getHandlePointer(L, 1));
    char* lpBuffer = lua_isnil(L, 2) ? NULL : getBuffer(L, 2);
    DWORD nBufferSize = luaL_checkinteger(L, 3);
    DWORD* lpBytesRead = lua_isnil(L, 4) ? NULL : getPDWORD(L, 4);
    DWORD* lpTotalBytesAvail = lua_isnil(L, 5) ? NULL : getPDWORD(L, 5);
    DWORD* lpBytesLeftThisMessage = lua_isnil(L, 6) ? NULL : getPDWORD(L, 6);
    
    BOOL result = PeekNamedPipe(handle, lpBuffer, nBufferSize, lpBytesRead, lpTotalBytesAvail, lpBytesLeftThisMessage);

    lua_pushboolean(L, result);
    return 1;
}
