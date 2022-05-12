#ifndef LUAWINPIPE_WINPIPE_H
#define LUAWINPIPE_WINPIPE_H

#include "common.h"
#include "metaphandle.h"
#include <windows.h>

static void addLongConstant(lua_State* L, const char* name, unsigned long value);
static void addPointerConstant(lua_State* L, const char* name, void* value, const char* metatable);

#endif
