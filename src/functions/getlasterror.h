#ifndef LUAWINPIPE_GETLASTERROR_H
#define LUAWINPIPE_GETLASTERROR_H

#include "..\common.h"

namespace winpipe::functions {

int lib_GetLastError(lua_State* L);

}

#endif
