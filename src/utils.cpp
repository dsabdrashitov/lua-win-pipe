#include "utils.h"

int lib_mask(lua_State* L) {
    int top = lua_gettop(L);
    long long result = 0;
    for (int i = 1; i <= top; i++) {
        long long arg = luaL_checkinteger(L, i);
        result |= arg;
    }
    
    lua_pushinteger(L, result);
    return 1;
}
