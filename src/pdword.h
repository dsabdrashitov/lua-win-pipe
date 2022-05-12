#ifndef LUAWINPIPE_PDWORD_H
#define LUAWINPIPE_PDWORD_H

#include <windows.h>
#include "common.h"

void registerMetaPDWORD(lua_State* L);
DWORD* getPDWORD(lua_State* L, int index);
int lib_newPDWORD(lua_State* L);
int lib_getPDWORD(lua_State* L);

#endif
