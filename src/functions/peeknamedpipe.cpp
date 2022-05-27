#include "peeknamedpipe.h"

#include <windows.h>
#include "..\byteblock.h"
#include "..\bytebuffer.h"

namespace winpipe::functions {

int lib_PeekNamedPipe(lua_State* L) {
    HANDLE handle = *(winpipe::byteblock::getPHandle(L, 1));
    char* lpBuffer = lua_isnil(L, 2) ? NULL : getBuffer(L, 2);
    DWORD nBufferSize = luaL_checkinteger(L, 3);
    DWORD* lpBytesRead = lua_isnil(L, 4) ? NULL : winpipe::byteblock::getPDWORD(L, 4);
    DWORD* lpTotalBytesAvail = lua_isnil(L, 5) ? NULL : winpipe::byteblock::getPDWORD(L, 5);
    DWORD* lpBytesLeftThisMessage = lua_isnil(L, 6) ? NULL : winpipe::byteblock::getPDWORD(L, 6);
    
    BOOL result = PeekNamedPipe(handle, lpBuffer, nBufferSize, lpBytesRead, lpTotalBytesAvail, lpBytesLeftThisMessage);

    lua_pushboolean(L, result);
    return 1;
}

}
