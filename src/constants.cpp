#include "constants.h"

#include <windows.h>
#include "phandle.h"


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

    // CreateFile:dwDesiredAccess, mask
    addLongConstant(L, "GENERIC_READ", GENERIC_READ);
    addLongConstant(L, "GENERIC_WRITE", GENERIC_WRITE);
    // CreateFile:dwShareMode, mask
    addLongConstant(L, "FILE_NO_SHARE", 0);
    addLongConstant(L, "FILE_SHARE_DELETE", FILE_SHARE_DELETE);
    addLongConstant(L, "FILE_SHARE_READ", FILE_SHARE_READ);
    addLongConstant(L, "FILE_SHARE_WRITE", FILE_SHARE_WRITE);
    // CreateFile:dwCreationDisposition, only one of
    addLongConstant(L, "CREATE_ALWAYS", CREATE_ALWAYS);
    addLongConstant(L, "CREATE_NEW", CREATE_NEW);
    addLongConstant(L, "OPEN_ALWAYS", OPEN_ALWAYS);
    addLongConstant(L, "OPEN_EXISTING", OPEN_EXISTING);
    addLongConstant(L, "TRUNCATE_EXISTING", TRUNCATE_EXISTING);
    // CreateFile:dwFlagsAndAttributes, mask
    addLongConstant(L, "FILE_ATTRIBUTE_DEFAULT", 0);
    addLongConstant(L, "FILE_ATTRIBUTE_ARCHIVE", FILE_ATTRIBUTE_ARCHIVE);
    addLongConstant(L, "FILE_ATTRIBUTE_ENCRYPTED", FILE_ATTRIBUTE_ENCRYPTED);
    addLongConstant(L, "FILE_ATTRIBUTE_HIDDEN", FILE_ATTRIBUTE_HIDDEN);
    addLongConstant(L, "FILE_ATTRIBUTE_NORMAL", FILE_ATTRIBUTE_NORMAL);
    addLongConstant(L, "FILE_ATTRIBUTE_OFFLINE", FILE_ATTRIBUTE_OFFLINE);
    addLongConstant(L, "FILE_ATTRIBUTE_READONLY", FILE_ATTRIBUTE_READONLY);
    addLongConstant(L, "FILE_ATTRIBUTE_SYSTEM", FILE_ATTRIBUTE_SYSTEM);
    addLongConstant(L, "FILE_ATTRIBUTE_TEMPORARY", FILE_ATTRIBUTE_TEMPORARY);
    addLongConstant(L, "FILE_FLAG_BACKUP_SEMANTICS", FILE_FLAG_BACKUP_SEMANTICS);
    addLongConstant(L, "FILE_FLAG_DELETE_ON_CLOSE", FILE_FLAG_DELETE_ON_CLOSE);
    addLongConstant(L, "FILE_FLAG_NO_BUFFERING", FILE_FLAG_NO_BUFFERING);
    addLongConstant(L, "FILE_FLAG_OPEN_NO_RECALL", FILE_FLAG_OPEN_NO_RECALL);
    addLongConstant(L, "FILE_FLAG_OPEN_REPARSE_POINT", FILE_FLAG_OPEN_REPARSE_POINT);
    addLongConstant(L, "FILE_FLAG_OVERLAPPED", FILE_FLAG_OVERLAPPED);
    addLongConstant(L, "FILE_FLAG_POSIX_SEMANTICS", FILE_FLAG_POSIX_SEMANTICS);
    addLongConstant(L, "FILE_FLAG_RANDOM_ACCESS", FILE_FLAG_RANDOM_ACCESS);
    addLongConstant(L, "FILE_FLAG_SESSION_AWARE", FILE_FLAG_SESSION_AWARE);
    addLongConstant(L, "FILE_FLAG_SEQUENTIAL_SCAN", FILE_FLAG_SEQUENTIAL_SCAN);
    addLongConstant(L, "FILE_FLAG_WRITE_THROUGH", FILE_FLAG_WRITE_THROUGH);
    addLongConstant(L, "SECURITY_ANONYMOUS", SECURITY_ANONYMOUS);
    addLongConstant(L, "SECURITY_CONTEXT_TRACKING", SECURITY_CONTEXT_TRACKING);
    addLongConstant(L, "SECURITY_DELEGATION", SECURITY_DELEGATION);
    addLongConstant(L, "SECURITY_EFFECTIVE_ONLY", SECURITY_EFFECTIVE_ONLY);
    addLongConstant(L, "SECURITY_IDENTIFICATION", SECURITY_IDENTIFICATION);
    addLongConstant(L, "SECURITY_IMPERSONATION", SECURITY_IMPERSONATION);

    return 1;
}
