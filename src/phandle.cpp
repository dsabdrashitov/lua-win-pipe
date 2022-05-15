#include "phandle.h"

#include "utils.h"


const char* METATABLE_PHANDLE = "winpipe.pHANDLE";

void registerMetaPHandle(lua_State* L) {
    luaL_newmetatable(L, METATABLE_PHANDLE);
    // set __eq
    lua_pushstring(L, "__eq");
    lua_pushcfunction(L, meta_pointerEquals);
    lua_settable(L, -3);
    // remove metatable from stack
    lua_settop(L, -1);
}

HANDLE* getHandlePointer(lua_State* L, int index) {
    HANDLE* pHandle = (HANDLE*) luaL_checkudata(L, index, METATABLE_PHANDLE);
    luaL_argcheck(L, pHandle != NULL, index, "HANDLE* expected");
    return pHandle;
}

HANDLE* createHandlePointer(lua_State* L) {
    HANDLE* pHandle = (HANDLE*) lua_newuserdata(L, sizeof(HANDLE));
    luaL_getmetatable(L, METATABLE_PHANDLE);
    lua_setmetatable(L, -2);
    return pHandle;
}

void pushHandle(lua_State* L, HANDLE handle) {
    HANDLE* pHandle = createHandlePointer(L);
    *pHandle = handle;
}
