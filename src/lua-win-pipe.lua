lua_win_pipe = {}

-- Change path
local prev_path = package.path
local root_path = debug.getinfo(1).source:match("@(.*\\)") or ""
package.path = root_path .. "?.lua"

-- imports and libs
local winpipe = package.loadlib(root_path .. "winpipe.dll", "luaopen_winpipe")()

-- Restore path
package.path = prev_path

lua_win_pipe.dll = winpipe

for name, val in pairs(winpipe.winpipe_constants()) do
    lua_win_pipe[name] = val
end

lua_win_pipe.mask = winpipe.winpipe_mask
lua_win_pipe.CreateNamedPipe = winpipe.winpipe_CreateNamedPipe
lua_win_pipe.ConnectNamedPipe = winpipe.winpipe_ConnectNamedPipe
lua_win_pipe.CloseHandle = winpipe.winpipe_CloseHandle

return lua_win_pipe
