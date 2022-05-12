#include "peeknamedpipe.h"

#include <windows.h>
#include "..\phandle.h"
#include "..\bytebuffer.h"
#include "..\pdword.h"


int lib_PeekNamedPipe(lua_State* L) {
    HANDLE handle = *(getHandlePointer(L, 1));
    char* lpBuffer = getBuffer(L, 2);
    DWORD nBufferSize = luaL_checkinteger(L, 3);
    DWORD* lpBytesRead = getPDWORD(L, 4);
    DWORD* lpTotalBytesAvail = getPDWORD(L, 5);
    DWORD* lpBytesLeftThisMessage = getPDWORD(L, 6);
    
    BOOL result = PeekNamedPipe(handle, lpBuffer, nBufferSize, lpBytesRead, lpTotalBytesAvail, lpBytesLeftThisMessage);

    lua_pushboolean(L, result);
    return 1;
}
