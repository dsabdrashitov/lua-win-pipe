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
    for (long i = 0; i < b1.size; i++) {
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

void createByteBlock(lua_State* L, long size) {
    char* buffer = (char*) lua_newuserdata(L, sizeof(ByteBlock) + size);
    luaL_getmetatable(L, METATABLE_NAME);
    lua_setmetatable(L, -2);
    ByteBlock* block = (ByteBlock*) buffer;
    block->size = size;
    block->ptr = buffer + sizeof(ByteBlock);
}

static ByteBlock* getByteBlockPointer(lua_State* L, int index) {
    ByteBlock* blockPtr = (ByteBlock*) luaL_checkudata(L, index, METATABLE_NAME);
    luaL_argcheck(L, blockPtr != NULL, index, "ByteBlock expected");
    return blockPtr;
}

ByteBlock getByteBlock(lua_State* L, int index) {
    ByteBlock* blockPtr = getByteBlockPointer(L, index);
    return *blockPtr;
}

HANDLE* getPHandle(lua_State* L, int index) {
    ByteBlock block = getByteBlock(L, index);
    luaL_argcheck(L, sizeof(HANDLE) <= block.size, index, "ByteBlock size not enough to contain HANDLE");
    return (HANDLE*) block.ptr;
}

DWORD* getPDWORD(lua_State* L, int index) {
    ByteBlock block = getByteBlock(L, index);
    luaL_argcheck(L, sizeof(DWORD) <= block.size, index, "ByteBlock size not enough to contain DWORD");
    return (DWORD*) block.ptr;
}

int lib_alloc(lua_State* L) {
    long size = luaL_checkinteger(L, 1);
    createByteBlock(L, size);
    return 1;
}

int lib_setOffset(lua_State* L) {
    ByteBlock* blockPtr = getByteBlockPointer(L, 1);
    long offset = luaL_checkinteger(L, 2);

    long currentSize = blockPtr->size;
    long currentOffset = blockPtr->ptr - (((char*) blockPtr) + sizeof(ByteBlock));
    luaL_argcheck(L, offset <= currentOffset + currentSize, 2, "offset is out of block size");

    blockPtr->ptr = ((char*) blockPtr) + sizeof(ByteBlock) + offset;
    blockPtr->size = currentOffset + currentSize - offset;

    return 0;
}

int lib_getString(lua_State* L) {
    ByteBlock block = getByteBlock(L, 1);
    long size = luaL_checkinteger(L, 2);
    luaL_argcheck(L, size >= 0, 2, "negative size");
    luaL_argcheck(L, size <= block.size, 2, "position outside of block");
    
    lua_pushlstring(L, block.ptr, size);
    return 1;
}

int lib_getDWORD(lua_State* L) {
    DWORD* pVal = getPDWORD(L, 1);
    
    lua_pushinteger(L, *pVal);
    return 1;
}

int lib_setString(lua_State* L) {
    ByteBlock block = getByteBlock(L, 1);
    size_t len;
    const char* str = luaL_checklstring(L, 2, &len);
    luaL_argcheck(L, len <= block.size, 2, "position outside of byteblock");
    
    for (long i = 0; i < len; i++) {
        block.ptr[i] = str[i];
    }

    return 0;
}

int lib_setDWORD(lua_State* L) {
    DWORD* pVal = getPDWORD(L, 1);
    DWORD value = luaL_checkinteger(L, 2);
    
    *pVal = value;

    return 0;
}

}