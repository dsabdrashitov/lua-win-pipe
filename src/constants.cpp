#include "constants.h"

#include <windows.h>
#include "metaphandle.h"


static void addLongConstant(lua_State* L, const char* name, unsigned long value) {
    lua_pushstring(L, name);
    lua_pushnumber(L, value);
    lua_settable(L, -3);
}

static void addHandleConstant(lua_State* L, const char* name, HANDLE value) {
    lua_pushstring(L, name);
    pushHandle(L, value);
    lua_settable(L, -3);
}

int lib_constants(lua_State* L) {
    lua_newtable(L);
    
    // CreateNamedPipe:dwOpenMode, same for all
    addLongConstant(L, "PIPE_ACCESS_INBOUND", PIPE_ACCESS_INBOUND);
    addLongConstant(L, "PIPE_ACCESS_OUTBOUND", PIPE_ACCESS_OUTBOUND);
    addLongConstant(L, "PIPE_ACCESS_DUPLEX", PIPE_ACCESS_DUPLEX);
    // CreateNamedPipe:dwOpenMode, can differ
    addLongConstant(L, "FILE_FLAG_FIRST_PIPE_INSTANCE", FILE_FLAG_FIRST_PIPE_INSTANCE);
    addLongConstant(L, "FILE_FLAG_WRITE_THROUGH", FILE_FLAG_WRITE_THROUGH);
    addLongConstant(L, "FILE_FLAG_OVERLAPPED", FILE_FLAG_OVERLAPPED);
    addLongConstant(L, "WRITE_DAC", WRITE_DAC);
    addLongConstant(L, "WRITE_OWNER", WRITE_OWNER);
    addLongConstant(L, "ACCESS_SYSTEM_SECURITY", ACCESS_SYSTEM_SECURITY);
    // CreateNamedPipe:dwPipeMode, same for all
    addLongConstant(L, "PIPE_TYPE_BYTE", PIPE_TYPE_BYTE);
    addLongConstant(L, "PIPE_TYPE_MESSAGE", PIPE_TYPE_MESSAGE);
    // CreateNamedPipe:dwPipeMode, can differ
    addLongConstant(L, "PIPE_READMODE_BYTE", PIPE_READMODE_BYTE);
    addLongConstant(L, "PIPE_READMODE_MESSAGE", PIPE_READMODE_MESSAGE);
    addLongConstant(L, "PIPE_WAIT", PIPE_WAIT);
    addLongConstant(L, "PIPE_NOWAIT", PIPE_NOWAIT);
    addLongConstant(L, "PIPE_ACCEPT_REMOTE_CLIENTS", PIPE_ACCEPT_REMOTE_CLIENTS);
    addLongConstant(L, "PIPE_REJECT_REMOTE_CLIENTS", PIPE_REJECT_REMOTE_CLIENTS);
    // CreateNamedPipe:nMaxInstances
    addLongConstant(L, "PIPE_UNLIMITED_INSTANCES", PIPE_UNLIMITED_INSTANCES);
    // INVALID_HANDLE_VALUE
    addHandleConstant(L, "INVALID_HANDLE_VALUE", INVALID_HANDLE_VALUE);

    return 1;
}
