#include "pdword.h"


const char* METATABLE_PDWORD = "winpipe.PDWORD";

void registerMetaPDWORD(lua_State* L) {
    luaL_newmetatable(L, METATABLE_PDWORD);
    // remove metatable from stack
    lua_settop(L, -1);
}

DWORD* getPDWORD(lua_State* L, int index) {
    DWORD* pVal = (DWORD*) luaL_checkudata(L, index, METATABLE_PDWORD);
    luaL_argcheck(L, pVal != NULL, index, "DWORD* expected");
    return pVal;
}

int lib_newPDWORD(lua_State* L) {
    DWORD value = luaL_checkinteger(L, 1);

    DWORD* pVal = (DWORD*) lua_newuserdata(L, sizeof(DWORD));
    luaL_getmetatable(L, METATABLE_PDWORD);
    lua_setmetatable(L, -2);
    *pVal = value;
    
    return 1;
}

int lib_getPDWORD(lua_State* L) {
    DWORD value = *(getPDWORD(L, 1));
    lua_pushinteger(L, value);
    return 1;
}
