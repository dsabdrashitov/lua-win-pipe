lua_win_pipe = {}

-- Change path
local prev_path = package.path
local root_path = debug.getinfo(1).source:match("@(.*\\)") or ""
package.path = root_path .. "?.lua"

-- imports and libs
local winpipe = package.loadlib(root_path .. "winpipe.dll", "luaopen_winpipe")()

-- Restore path
package.path = prev_path

for name, val in pairs(winpipe.winpipe_constants()) do
    lua_win_pipe[name] = val
end

lua_win_pipe.mask = winpipe.winpipe_mask
lua_win_pipe.newBuffer = winpipe.winpipe_newBuffer
lua_win_pipe.getBuffer = winpipe.winpipe_getBuffer
lua_win_pipe.toBuffer = winpipe.winpipe_toBuffer
lua_win_pipe.newPDWORD = winpipe.winpipe_newPDWORD
lua_win_pipe.getPDWORD = winpipe.winpipe_getPDWORD

lua_win_pipe.CreateNamedPipe = winpipe.winpipe_CreateNamedPipe
lua_win_pipe.CreateFile = winpipe.winpipe_CreateFile
lua_win_pipe.ConnectNamedPipe = winpipe.winpipe_ConnectNamedPipe
lua_win_pipe.CloseHandle = winpipe.winpipe_CloseHandle
lua_win_pipe.PeekNamedPipe = winpipe.winpipe_PeekNamedPipe
lua_win_pipe.ReadFile = winpipe.winpipe_ReadFile
lua_win_pipe.WriteFile = winpipe.winpipe_WriteFile

return lua_win_pipe
