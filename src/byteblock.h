#ifndef LUAWINPIPE_BYTEBLOCK_H
#define LUAWINPIPE_BYTEBLOCK_H

#include "common.h"
#include <windows.h>

namespace winpipe::byteblock {

typedef struct {
    long size;
    char* ptr;
} ByteBlock;

void registerMeta(lua_State* L);
void createByteBlock(lua_State* L, long size);
ByteBlock getByteBlock(lua_State* L, int index);
HANDLE* getPHandle(lua_State* L, int index);
DWORD* getPDWORD(lua_State* L, int index);

int lib_alloc(lua_State* L);
int lib_setOffset(lua_State* L);
int lib_getString(lua_State* L);
int lib_getDWORD(lua_State* L);
int lib_setString(lua_State* L);
int lib_setDWORD(lua_State* L);

}

#endif
