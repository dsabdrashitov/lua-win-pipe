#include "bytebuffer.h"


const char* METATABLE_BUFFER = "winpipe.buffer";

void registerMetaBuffer(lua_State* L) {
    luaL_newmetatable(L, METATABLE_BUFFER);
    // pointerEquals cant be applied to buffer, because buffer is not pointer to pointer :(
    // so there is no __eq setting
    // remove metatable from stack
    lua_settop(L, -1);
}

char* getBuffer(lua_State* L, int index) {
    char* buffer = (char*) luaL_checkudata(L, index, METATABLE_BUFFER);
    luaL_argcheck(L, buffer != NULL, index, "char* expected");
    return buffer;
}

static char* newBuffer(lua_State* L, int size) {
    char* buffer = (char*) lua_newuserdata(L, size);
    luaL_getmetatable(L, METATABLE_BUFFER);
    lua_setmetatable(L, -2);
    return buffer;
}

int lib_newBuffer(lua_State* L) {
    int size = luaL_checkinteger(L, 1);
    char* buffer = newBuffer(L, size);
    return 1;
}

int lib_fromBuffer(lua_State* L) {
    char* buffer = getBuffer(L, 1);
    int count = luaL_checkinteger(L, 2);

    lua_pushlstring(L, buffer, count);

    return 1;
}

int lib_toBuffer(lua_State* L) {
    char* buffer = getBuffer(L, 1);
    size_t len;
    const char* str = luaL_checklstring(L, 2, &len);
    
    for (int i = 0; i < len; i++) {
        buffer[i] = str[i];
    }
    
    lua_pushnil(L);
    return 1;
}
