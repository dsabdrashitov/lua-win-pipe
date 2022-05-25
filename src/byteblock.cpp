#include "byteblock.h"

namespace winpipe::byteblock {

static const char* METATABLE_NAME = "winpipe.byteblock";

static int equals(lua_State* L) {
    ByteBlock b1 = getByteBlock(L, 1);
    ByteBlock b2 = getByteBlock(L, 2);
    if (b1.size != b2.size) {
        lua_pushboolean(L, false);
        return 1;
    }
    for (int i = 0; i < b1.size; i++) {
        if (b1.ptr[i] != b2.ptr[i]) {
            lua_pushboolean(L, false);
            return 1;
        }
    }
    lua_pushboolean(L, true);
    return 1;
}

void registerMeta(lua_State* L) {
    luaL_newmetatable(L, METATABLE_NAME);
    // set __eq
    lua_pushstring(L, "__eq");
    lua_pushcfunction(L, equals);
    lua_settable(L, -3);
    // remove metatable from stack
    lua_settop(L, -1);
}

void createByteBlock(lua_State* L, int size) {
    char* buffer = (char*) lua_newuserdata(L, sizeof(ByteBlock) + size);
    luaL_getmetatable(L, METATABLE_NAME);
    lua_setmetatable(L, -2);
    ByteBlock* block = (ByteBlock*) buffer;
    block->size = size;
    block->ptr = buffer + sizeof(ByteBlock);
}

ByteBlock getByteBlock(lua_State* L, int index) {
    ByteBlock* blockPtr = (ByteBlock*) luaL_checkudata(L, index, METATABLE_NAME);
    luaL_argcheck(L, blockPtr != NULL, index, "ByteBlock expected");
    return *blockPtr;
}

HANDLE* getPHandle(lua_State* L, int index) {
    ByteBlock block = getByteBlock(L, index);
    luaL_argcheck(L, sizeof(HANDLE) == block.size, index, "ByteBlock size not equals to size of HANDLE");
    return (HANDLE*) block.ptr;
}

DWORD* getPDWORD(lua_State* L, int index) {
    ByteBlock block = getByteBlock(L, index);
    luaL_argcheck(L, sizeof(DWORD) == block.size, index, "ByteBlock size not equals to size of DWORD");
    return (DWORD*) block.ptr;
}

int lib_alloc(lua_State* L) {
    int size = luaL_checkinteger(L, 1);
    createByteBlock(L, size);
    return 1;
}

int lib_getString(lua_State* L) {
    ByteBlock block = getByteBlock(L, 1);
    int offset = luaL_checkinteger(L, 2);
    int size = luaL_checkinteger(L, 3);
    luaL_argcheck(L, size >= 0, 3, "negative size");
    luaL_argcheck(L, offset + size <= block.size, 3, "position outside of byteblock");
    
    lua_pushlstring(L, block.ptr + offset, size);
    return 1;
}

int lib_getDWORD(lua_State* L) {
    ByteBlock block = getByteBlock(L, 1);
    luaL_argcheck(L, sizeof(DWORD) == block.size, 1, "ByteBlock size not equals to size of DWORD");

    lua_pushinteger(L, *((DWORD*) block.ptr));
    return 1;
}

int lib_setString(lua_State* L) {
    ByteBlock block = getByteBlock(L, 1);
    int offset = luaL_checkinteger(L, 2);
    size_t len;
    const char* str = luaL_checklstring(L, 3, &len);
    luaL_argcheck(L, offset + len <= block.size, 2, "position outside of byteblock");
    
    for (int i = 0; i < len; i++) {
        block.ptr[offset + i] = str[i];
    }

    lua_pushnil(L);
    return 1;
}

int lib_setDWORD(lua_State* L) {
    ByteBlock block = getByteBlock(L, 1);
    DWORD value = luaL_checkinteger(L, 2);
    luaL_argcheck(L, sizeof(DWORD) == block.size, 1, "ByteBlock size not equals to size of DWORD");

    *((DWORD*) block.ptr) = value;

    lua_pushnil(L);
    return 1;
}

}