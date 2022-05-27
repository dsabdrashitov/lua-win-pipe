#include "winpipe.h"

#include <windows.h>
#include "byteblock.h"
#include "bytebuffer.h"
#include "constants.h"
#include "phandle.h"
#include "utils.h"
#include "functions\closehandle.h"
#include "functions\connectnamedpipe.h"
#include "functions\createfile.h"
#include "functions\createnamedpipe.h"
#include "functions\getlasterror.h"
#include "functions\peeknamedpipe.h"
#include "functions\readfile.h"
#include "functions\waitnamedpipe.h"
#include "functions\writefile.h"


// DLL entry point
BOOL APIENTRY DllMain(HANDLE hModule, DWORD  fdwReason, LPVOID lpReserved) {
    return TRUE;
}

static const struct luaL_Reg library_functions[] = {
    {"winpipe_ConnectNamedPipe", lib_ConnectNamedPipe},
    {"winpipe_CloseHandle", lib_CloseHandle},
    {"winpipe_CreateFile", lib_CreateFile},
    {"winpipe_CreateNamedPipe", lib_CreateNamedPipe},
    {"winpipe_GetLastError", lib_GetLastError},
    {"winpipe_PeekNamedPipe", lib_PeekNamedPipe},
    {"winpipe_ReadFile", lib_ReadFile},
    {"winpipe_WaitNamedPipe", lib_WaitNamedPipe},
    {"winpipe_WriteFile", lib_WriteFile},
    
    {"winpipe_constants", lib_constants},
    {"winpipe_mask", lib_mask},
    {"winpipe_ByteBlock_alloc", winpipe::byteblock::lib_alloc},
    {"winpipe_ByteBlock_setOffset", winpipe::byteblock::lib_setOffset},
    {"winpipe_ByteBlock_getString", winpipe::byteblock::lib_getString},
    {"winpipe_ByteBlock_getDWORD", winpipe::byteblock::lib_getDWORD},
    {"winpipe_ByteBlock_setString", winpipe::byteblock::lib_setString},
    {"winpipe_ByteBlock_setDWORD", winpipe::byteblock::lib_setDWORD},
    {"winpipe_fromBuffer", lib_fromBuffer},
    {"winpipe_newBuffer", lib_newBuffer},
    {"winpipe_toBuffer", lib_toBuffer},
    {NULL, NULL}
};

extern "C" LUALIB_API int luaopen_winpipe(lua_State* L) {
    winpipe::byteblock::registerMeta(L);
    registerMetaPHandle(L);
    registerMetaBuffer(L);
    luaL_newlib(L, library_functions);
    return 1;
}
