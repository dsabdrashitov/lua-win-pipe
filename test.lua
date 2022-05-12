-- Change path
local prev_path = package.path
local root_path = debug.getinfo(1).source:match("@(.*\\)") or ""
package.path = root_path .. "?.lua"

-- imports and libs
lwp = require("build.lua-win-pipe.lua-win-pipe")

-- Restore path
package.path = prev_path

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
print("open: " .. tostring(lwp.INVALID_HANDLE_VALUE ~= handle))

print("connect: " .. tostring(lwp.ConnectNamedPipe(handle, nil)))

local bufsize = 10
local buf = lwp.newBuffer(bufsize)
local lpBytesRead = lwp.newPDWORD(0)
local lpTotalBytesAvail = lwp.newPDWORD(0)
local lpBytesLeftThisMessage = lwp.newPDWORD(0)
print("peek: " .. tostring(
        lwp.PeekNamedPipe(handle, buf, bufsize, lpBytesRead, lpTotalBytesAvail, lpBytesLeftThisMessage)))

print('"' .. tostring(lwp.getBuffer(buf, bufsize)) .. "'")
print(lwp.getPDWORD(lpBytesRead))
print(lwp.getPDWORD(lpTotalBytesAvail))
print(lwp.getPDWORD(lpBytesLeftThisMessage))

print("close: " .. tostring(lwp.CloseHandle(handle)))
