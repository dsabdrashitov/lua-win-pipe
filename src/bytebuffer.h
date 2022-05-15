#ifndef LUAWINPIPE_BYTEBUFFER_H
#define LUAWINPIPE_BYTEBUFFER_H

#include "common.h"

void registerMetaBuffer(lua_State* L);
char* getBuffer(lua_State* L, int index);
int lib_newBuffer(lua_State* L);
int lib_getBuffer(lua_State* L);
int lib_toBuffer(lua_State* L);

#endif
