#include "utils.h"

int pointerEquals(lua_State* L) {
    void** p1 = (void**) lua_touserdata(L, 1);
    void** p2 = (void**) lua_touserdata(L, 2);
    bool result = (*p1 == *p2);
    lua_pushboolean(L, result);
    return 1;
}
