-- Change path
local prev_path = package.path
local root_path = debug.getinfo(1).source:match("@(.*\\)") or ""
package.path = root_path .. "?.lua"

-- imports and libs
lua_win_pipe = require("build.lua-win-pipe.lua-win-pipe")

-- Restore path
package.path = prev_path

for name, val in pairs(lua_win_pipe.dll.winpipe_constants()) do
    print(name .. ": " .. val)
end
