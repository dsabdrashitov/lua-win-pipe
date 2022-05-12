#include "utils.h"

int meta_pointerEquals(lua_State* L) {
    void** p1 = (void**) lua_touserdata(L, 1);
    void** p2 = (void**) lua_touserdata(L, 2);
    bool result = (*p1 == *p2);

    lua_pushboolean(L, result);
    return 1;
}

int lib_mask(lua_State* L) {
    int top = lua_gettop(L);
    long long result = 0;
    for (int i = 1; i <= top; i++) {
        long long arg = luaL_checkinteger(L, i);
        result |= arg;
    }
    
    lua_pushnumber(L, result);
    return 1;
}
