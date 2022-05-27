#include "winpipe.h"

#include <windows.h>
#include "byteblock.h"
#include "bytebuffer.h"
#include "constants.h"
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
    {"winpipe_ConnectNamedPipe", winpipe::functions::lib_ConnectNamedPipe},
    {"winpipe_CloseHandle", winpipe::functions::lib_CloseHandle},
    {"winpipe_CreateFile", winpipe::functions::lib_CreateFile},
    {"winpipe_CreateNamedPipe", winpipe::functions::lib_CreateNamedPipe},
    {"winpipe_GetLastError", winpipe::functions::lib_GetLastError},
    {"winpipe_PeekNamedPipe", winpipe::functions::lib_PeekNamedPipe},
    {"winpipe_ReadFile", winpipe::functions::lib_ReadFile},
    {"winpipe_WaitNamedPipe", winpipe::functions::lib_WaitNamedPipe},
    {"winpipe_WriteFile", winpipe::functions::lib_WriteFile},
    
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
    registerMetaBuffer(L);
    luaL_newlib(L, library_functions);
    return 1;
}
