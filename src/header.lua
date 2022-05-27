---
--- Just header file allowing IDEs to autocomplete methods from this library.
--- Don't need to require or somehow import it into a code.
---

-- Constants.
-- CreateNamedPipe:dwOpenMode, same for all
PIPE_ACCESS_INBOUND = PIPE_ACCESS_INBOUND
PIPE_ACCESS_OUTBOUND = PIPE_ACCESS_OUTBOUND
PIPE_ACCESS_DUPLEX = PIPE_ACCESS_DUPLEX
-- CreateNamedPipe:dwOpenMode, can differ
FILE_FLAG_FIRST_PIPE_INSTANCE = FILE_FLAG_FIRST_PIPE_INSTANCE
FILE_FLAG_WRITE_THROUGH = FILE_FLAG_WRITE_THROUGH
FILE_FLAG_OVERLAPPED = FILE_FLAG_OVERLAPPED
WRITE_DAC = WRITE_DAC
WRITE_OWNER = WRITE_OWNER
ACCESS_SYSTEM_SECURITY = ACCESS_SYSTEM_SECURITY
-- CreateNamedPipe:dwPipeMode, same for all
PIPE_TYPE_BYTE = PIPE_TYPE_BYTE
PIPE_TYPE_MESSAGE = PIPE_TYPE_MESSAGE
-- CreateNamedPipe:dwPipeMode, can differ
PIPE_READMODE_BYTE = PIPE_READMODE_BYTE
PIPE_READMODE_MESSAGE = PIPE_READMODE_MESSAGE
PIPE_WAIT = PIPE_WAIT
PIPE_NOWAIT = PIPE_NOWAIT
PIPE_ACCEPT_REMOTE_CLIENTS = PIPE_ACCEPT_REMOTE_CLIENTS
PIPE_REJECT_REMOTE_CLIENTS = PIPE_REJECT_REMOTE_CLIENTS
-- CreateNamedPipe:nMaxInstances
PIPE_UNLIMITED_INSTANCES = PIPE_UNLIMITED_INSTANCES
-- INVALID_HANDLE_VALUE
INVALID_HANDLE_VALUE = INVALID_HANDLE_VALUE
-- SIZEOF_DWORD
SIZEOF_DWORD = SIZEOF_DWORD
-- CreateFile:dwDesiredAccess, mask
GENERIC_READ = GENERIC_READ
GENERIC_WRITE = GENERIC_WRITE
-- CreateFile:dwShareMode, mask
FILE_NO_SHARE = 0
FILE_SHARE_DELETE = FILE_SHARE_DELETE
FILE_SHARE_READ = FILE_SHARE_READ
FILE_SHARE_WRITE = FILE_SHARE_WRITE
-- CreateFile:dwCreationDisposition, only one of
CREATE_ALWAYS = CREATE_ALWAYS
CREATE_NEW = CREATE_NEW
OPEN_ALWAYS = OPEN_ALWAYS
OPEN_EXISTING = OPEN_EXISTING
TRUNCATE_EXISTING = TRUNCATE_EXISTING
-- CreateFile:dwFlagsAndAttributes, mask
FILE_ATTRIBUTE_DEFAULT = 0
FILE_ATTRIBUTE_ARCHIVE = FILE_ATTRIBUTE_ARCHIVE
FILE_ATTRIBUTE_ENCRYPTED = FILE_ATTRIBUTE_ENCRYPTED
FILE_ATTRIBUTE_HIDDEN = FILE_ATTRIBUTE_HIDDEN
FILE_ATTRIBUTE_NORMAL = FILE_ATTRIBUTE_NORMAL
FILE_ATTRIBUTE_OFFLINE = FILE_ATTRIBUTE_OFFLINE
FILE_ATTRIBUTE_READONLY = FILE_ATTRIBUTE_READONLY
FILE_ATTRIBUTE_SYSTEM = FILE_ATTRIBUTE_SYSTEM
FILE_ATTRIBUTE_TEMPORARY = FILE_ATTRIBUTE_TEMPORARY
FILE_FLAG_BACKUP_SEMANTICS = FILE_FLAG_BACKUP_SEMANTICS
FILE_FLAG_DELETE_ON_CLOSE = FILE_FLAG_DELETE_ON_CLOSE
FILE_FLAG_NO_BUFFERING = FILE_FLAG_NO_BUFFERING
FILE_FLAG_OPEN_NO_RECALL = FILE_FLAG_OPEN_NO_RECALL
FILE_FLAG_OPEN_REPARSE_POINT = FILE_FLAG_OPEN_REPARSE_POINT
FILE_FLAG_OVERLAPPED = FILE_FLAG_OVERLAPPED
FILE_FLAG_POSIX_SEMANTICS = FILE_FLAG_POSIX_SEMANTICS
FILE_FLAG_RANDOM_ACCESS = FILE_FLAG_RANDOM_ACCESS
FILE_FLAG_SESSION_AWARE = FILE_FLAG_SESSION_AWARE
FILE_FLAG_SEQUENTIAL_SCAN = FILE_FLAG_SEQUENTIAL_SCAN
FILE_FLAG_WRITE_THROUGH = FILE_FLAG_WRITE_THROUGH
SECURITY_ANONYMOUS = SECURITY_ANONYMOUS
SECURITY_CONTEXT_TRACKING = SECURITY_CONTEXT_TRACKING
SECURITY_DELEGATION = SECURITY_DELEGATION
SECURITY_EFFECTIVE_ONLY = SECURITY_EFFECTIVE_ONLY
SECURITY_IDENTIFICATION = SECURITY_IDENTIFICATION
SECURITY_IMPERSONATION = SECURITY_IMPERSONATION

-- Errors.
-- WriteFile
ERROR_IO_PENDING = ERROR_IO_PENDING
ERROR_INVALID_USER_BUFFER = ERROR_INVALID_USER_BUFFER
ERROR_NOT_ENOUGH_MEMORY = ERROR_NOT_ENOUGH_MEMORY
ERROR_OPERATION_ABORTED = ERROR_OPERATION_ABORTED
ERROR_NOT_ENOUGH_QUOTA = ERROR_NOT_ENOUGH_QUOTA
ERROR_BROKEN_PIPE = ERROR_BROKEN_PIPE
-- ReadFile
ERROR_INSUFFICIENT_BUFFER = ERROR_INSUFFICIENT_BUFFER
ERROR_HANDLE_EOF = ERROR_HANDLE_EOF
ERROR_MORE_DATA = ERROR_MORE_DATA
-- CreateNamedPipe
ERROR_ACCESS_DENIED = ERROR_ACCESS_DENIED
ERROR_INVALID_PARAMETER = ERROR_INVALID_PARAMETER
-- CreateFile
ERROR_SHARING_VIOLATION = ERROR_SHARING_VIOLATION
ERROR_ALREADY_EXISTS = ERROR_ALREADY_EXISTS
ERROR_FILE_EXISTS = ERROR_FILE_EXISTS
ERROR_FILE_NOT_FOUND = ERROR_FILE_NOT_FOUND
ERROR_PIPE_BUSY = ERROR_PIPE_BUSY
-- WaitNamedPipe
ERROR_SEM_TIMEOUT = ERROR_SEM_TIMEOUT
-- CloseHandle
ERROR_INVALID_HANDLE = ERROR_INVALID_HANDLE
-- ConnectNamedPipe
ERROR_PIPE_CONNECTED = ERROR_PIPE_CONNECTED
ERROR_NO_DATA = ERROR_NO_DATA
ERROR_PIPE_LISTENING = ERROR_PIPE_LISTENING


-- returns logical or of masks in arguments
function mask(mask1, ...) return 0 end

-- creates new block of bytes in C and returns it as userdata
function ByteBlock_alloc(intSizeInBytes) return userdata() end

-- changes viewpoint of byteblock ot intOffset from the start of block
function ByteBlock_setOffset(udBlock, intOffset) end

-- returns intCount bytes in block of bytes as lua string
function ByteBlock_getString(udBlock, intCount) return "" end

-- returns contents of byte block as it was DWORD (size of block shoud equals size of DWORD)
function ByteBlock_getDWORD(udBlock) return 0 end

-- copies bytes of lua string strData to C char*
function ByteBlock_setString(udBlock, strData) end

-- set contents of byte block to value of intValue
function ByteBlock_setDWORD(udBlock, intValue) end

-- creates new char* array in C and returns it as userdata
function newBuffer(intSizeInBytes) return userdata() end

-- returns first intCount bytes of udBuffer as lua string
function fromBuffer(udBuffer, intCount) return "" end

-- copies lua string strData to C char* udBuffer
function toBuffer(udBuffer, strData) return nil end


-- wrapped functions from <windows.h>
function CloseHandle(udHandle)
    return false
end
function ConnectNamedPipe(udHandle, nilOverlapped)
    return false
end
function CreateFile(strName, intDesiredAccess, intShareMode, nilSecurityAttributes,
                    intCreationDisposition, intFlagsAndAttributes, nilTemplateFile)
    return userdata()
end
function CreateNamedPipe(strName, intOpenMode, intPipeMode, intMaxInstances,
                         intOutBufferSize, intInBufferSize, intTimeoutMs, nilSecurityAttributes)
    return userdata()
end
function GetLastError()
    return 0
end
function PeekNamedPipe(udHandle, udBuffer, intBufferSize, pdwBytesRead, pdwTotalBytesAvail, pdwBytesLeftThisMessage)
    return false
end
function ReadFile(udHandle, udBuffer, intBufferSize, pdwBytesRead, nilOverlapped)
    return false
end
function WaitNamedPipe(strName, intTimeOut)
    return false
end
function WriteFile(udHandle, udBuffer, intBytesToWrite, pdwBytesWritten, nilOverlapped)
    return false
end
