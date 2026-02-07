#include "peeknamedpipe.h"

#include <windows.h>
#include "..\byteblock.h"

namespace winpipe::functions {

int lib_PeekNamedPipe(lua_State* L) {
    HANDLE handle = *(winpipe::byteblock::getPHandle(L, 1));
    winpipe::byteblock::ByteBlock udBuffer = lua_isnil(L, 2) ? 
        (winpipe::byteblock::ByteBlock) {0, NULL} : 
        winpipe::byteblock::getByteBlock(L, 2);
    DWORD nBufferSize = luaL_checkinteger(L, 3);
    luaL_argcheck(L, nBufferSize <= udBuffer.size, 3, "not enough space in buffer");
    DWORD* lpBytesRead = lua_isnil(L, 4) ? NULL : winpipe::byteblock::getPDWORD(L, 4);
    DWORD* lpTotalBytesAvail = lua_isnil(L, 5) ? NULL : winpipe::byteblock::getPDWORD(L, 5);
    DWORD* lpBytesLeftThisMessage = lua_isnil(L, 6) ? NULL : winpipe::byteblock::getPDWORD(L, 6);
    
    BOOL result = PeekNamedPipe(handle, udBuffer.ptr, nBufferSize, lpBytesRead, lpTotalBytesAvail, lpBytesLeftThisMessage);
    winpipe::g_LastStoredError = GetLastError();
    
    lua_pushboolean(L, result);
    return 1;
}

}
