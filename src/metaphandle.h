#ifndef LUAWINPIPE_METAPHANDLE_H
#define LUAWINPIPE_METAPHANDLE_H

#include "common.h"
#include "utils.h"
#include <windows.h>

void registerMetaPHandle(lua_State* L);
HANDLE* getHandlePointer(lua_State* L, int index);
HANDLE* createHandlePointer(lua_State* L);
void pushHandlePointer(lua_State* L, HANDLE handle);

#endif
