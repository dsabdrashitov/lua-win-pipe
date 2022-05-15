#include "createfile.h"

#include <windows.h>
#include "..\phandle.h"


int lib_CreateFile(lua_State* L) {   
   const char* pName = luaL_checkstring(L, 1);
   DWORD dwDesiredAccess = luaL_checkinteger(L, 2);
   DWORD dwShareMode = luaL_checkinteger(L, 3);
   luaL_argcheck(L, lua_isnil(L, 4), 4, "nil expected");
   DWORD dwCreateDisposition = luaL_checkinteger(L, 5);
   DWORD dwFlagsAndAttributes = luaL_checkinteger(L, 6);
   luaL_argcheck(L, lua_isnil(L, 7), 7, "nil expected");

   HANDLE* pHandle = createHandlePointer(L);
   
   *pHandle = CreateFile(
         pName,
         dwDesiredAccess,
         dwShareMode,
         NULL,
         dwCreateDisposition,
         dwFlagsAndAttributes,
         NULL);
   
   return 1;
}
