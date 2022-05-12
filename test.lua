-- Change path
local prev_path = package.path
local root_path = debug.getinfo(1).source:match("@(.*\\)") or ""
package.path = root_path .. "?.lua"

-- imports and libs
lwp = require("build.lua-win-pipe.lua-win-pipe")

-- Restore path
package.path = prev_path

local buf = lwp.newBuffer(10)
print(buf)
print("'" .. lwp.getBuffer(buf, 10) .. '"')
buf = lwp.toBuffer("hello:)")
print(buf)
print("'" .. lwp.getBuffer(buf, ("hello:)__"):len()) .. '"')

print(lwp.mask(
        lwp.FILE_FLAG_FIRST_PIPE_INSTANCE,
        lwp.FILE_FLAG_WRITE_THROUGH,
        lwp.FILE_FLAG_OVERLAPPED
))

print(lwp.INVALID_HANDLE_VALUE == lwp.INVALID_HANDLE_VALUE)
print(lwp.INVALID_HANDLE_VALUE ~= lwp.INVALID_HANDLE_VALUE)

local handle = lwp.CreateNamedPipe(
        "\\\\.\\pipe\\testPipe",
        lwp.PIPE_ACCESS_DUPLEX,
        lwp.mask(lwp.PIPE_TYPE_MESSAGE, lwp.PIPE_READMODE_MESSAGE, lwp.PIPE_WAIT),
        lwp.PIPE_UNLIMITED_INSTANCES,
        512,
        512,
        5000,
        nil
)

print(handle == lwp.INVALID_HANDLE_VALUE)
print(lwp.INVALID_HANDLE_VALUE ~= handle)

print(lwp.ConnectNamedPipe(handle, nil))

print(lwp.CloseHandle(handle))
