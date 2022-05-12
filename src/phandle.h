#ifndef LUAWINPIPE_PHANDLE_H
#define LUAWINPIPE_PHANDLE_H

#include "common.h"
#include <windows.h>

void registerMetaPHandle(lua_State* L);
HANDLE* getHandlePointer(lua_State* L, int index);
HANDLE* createHandlePointer(lua_State* L);
void pushHandle(lua_State* L, HANDLE handle);

#endif
