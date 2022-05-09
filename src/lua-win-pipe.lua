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

return lua_win_pipe
