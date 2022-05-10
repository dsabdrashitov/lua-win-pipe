-- Change path
local prev_path = package.path
local root_path = debug.getinfo(1).source:match("@(.*\\)") or ""
package.path = root_path .. "?.lua"

-- imports and libs
lua_win_pipe = require("build.lua-win-pipe.lua-win-pipe")

-- Restore path
package.path = prev_path

print(lua_win_pipe.mask(
        lua_win_pipe.FILE_FLAG_FIRST_PIPE_INSTANCE,
        lua_win_pipe.FILE_FLAG_WRITE_THROUGH,
        lua_win_pipe.FILE_FLAG_OVERLAPPED
))

print(lua_win_pipe.INVALID_HANDLE_VALUE == lua_win_pipe.INVALID_HANDLE_VALUE)
print(lua_win_pipe.INVALID_HANDLE_VALUE ~= lua_win_pipe.INVALID_HANDLE_VALUE)

local handle = lua_win_pipe.CreateNamedPipe(
        "\\\\.\\pipe\\testPipe",
        lua_win_pipe.PIPE_ACCESS_DUPLEX,
        lua_win_pipe.mask(lua_win_pipe.PIPE_TYPE_MESSAGE, lua_win_pipe.PIPE_READMODE_MESSAGE, lua_win_pipe.PIPE_WAIT),
        lua_win_pipe.PIPE_UNLIMITED_INSTANCES,
        512,
        512,
        5000,
        nil
)

print(handle == lua_win_pipe.INVALID_HANDLE_VALUE)
print(lua_win_pipe.INVALID_HANDLE_VALUE == handle)

print(lua_win_pipe.CloseHandle(handle))
