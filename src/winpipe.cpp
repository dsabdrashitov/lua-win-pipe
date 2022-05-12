#include "winpipe.h"

#include <windows.h>
#include "bytebuffer.h"
#include "constants.h"
#include "phandle.h"
#include "utils.h"
#include "functions\createnamedpipe.h"
#include "functions\connectnamedpipe.h"
#include "functions\closehandle.h"


// DLL entry point
BOOL APIENTRY DllMain(HANDLE hModule, DWORD  fdwReason, LPVOID lpReserved) {
    return TRUE;
}

static const struct luaL_Reg library_functions[] = {
    {"winpipe_CreateNamedPipe", lib_CreateNamedPipe},
    {"winpipe_ConnectNamedPipe", lib_ConnectNamedPipe},
    {"winpipe_CloseHandle", lib_CloseHandle},
    {"winpipe_constants", lib_constants},
    {"winpipe_mask", lib_mask},
    {"winpipe_getBuffer", lib_getBuffer},
    {"winpipe_newBuffer", lib_newBuffer},
    {"winpipe_toBuffer", lib_toBuffer},
    {NULL, NULL}
};

extern "C" LUALIB_API int luaopen_winpipe(lua_State* L) {
    registerMetaPHandle(L);
    registerMetaBuffer(L);
    luaL_newlib(L, library_functions);
    return 1;
}
