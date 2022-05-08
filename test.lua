
-- Change paths
local prev_path = package.path
print(prev_path)
print(debug.getinfo(1).source)
local root_path = debug.getinfo(1).source:match("@(.*)test.lua")
print(root_path)
package.path = root_path .. "?.lua"
print(package.path)
local winpipe = package.loadlib(root_path .. "build/lua-win-pipe/winpipe.dll", "luaopen_winpipe")()
package.path = prev_path

print(winpipe.somefunc())
for name, val in pairs(winpipe.constants()) do
    print(name .. ": " .. val)
end
