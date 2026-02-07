#include "writefile.h"

#include <windows.h>
#include "..\byteblock.h"

namespace winpipe::functions {

int lib_WriteFile(lua_State* L) {
    HANDLE handle = *(winpipe::byteblock::getPHandle(L, 1));
    winpipe::byteblock::ByteBlock udBuffer = lua_isnil(L, 2) ? 
        (winpipe::byteblock::ByteBlock) {0, NULL} : 
        winpipe::byteblock::getByteBlock(L, 2);
    DWORD nNumberOfBytesToWrite = luaL_checkinteger(L, 3);
    luaL_argcheck(L, nNumberOfBytesToWrite <= udBuffer.size, 3, "not enough space in buffer");
    DWORD* lpBytesWritten = lua_isnil(L, 4) ? NULL : winpipe::byteblock::getPDWORD(L, 4);
    luaL_argcheck(L, lua_isnil(L, 5), 5, "nil expected");
    
    BOOL result = WriteFile(handle, udBuffer.ptr, nNumberOfBytesToWrite, lpBytesWritten, NULL);
    winpipe::g_LastStoredError = GetLastError();

    lua_pushboolean(L, result);
    return 1;
}

}
