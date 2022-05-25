-- Change path
local prev_path = package.path
local root_path = debug.getinfo(1).source:match("@(.*\\)") or ""
package.path = root_path .. "?.lua"

-- imports and libs
lwp = require("build.lua-win-pipe.lua-win-pipe")

-- Restore path
package.path = prev_path

function main()
    local udDword = lwp.ByteBlock_alloc(lwp.SIZEOF_DWORD)
    lwp.ByteBlock_setDWORD(udDword, 655360)
    print(lwp.ByteBlock_getDWORD(udDword))

    local strConst = "Hello, World!!!"
    local udStr = lwp.ByteBlock_alloc(strConst:len())
    lwp.ByteBlock_setString(udStr, 0, strConst)
    print(lwp.ByteBlock_getString(udStr, 1, 14))
    lwp.ByteBlock_setString(udStr, 3, "zxy111")
    print(lwp.ByteBlock_getString(udStr, 0, strConst:len()))
end

main()
