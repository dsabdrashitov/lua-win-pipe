-- Change path
local prev_path = package.path
local root_path = debug.getinfo(1).source:match("@(.*\\)") or ""
package.path = root_path .. "?.lua"

-- imports and libs
lwp = require("build.lua-win-pipe.lua-win-pipe")

-- Restore path
package.path = prev_path

function main()
    local hPipe = lwp.CreateFile(
            "\\\\.\\pipe\\lwp_test",
            lwp.mask(lwp.GENERIC_READ, lwp.GENERIC_WRITE),
            lwp.FILE_NO_SHARE,
            nil,
            lwp.OPEN_EXISTING,
            lwp.FILE_ATTRIBUTE_DEFAULT,
            nil
    )

    if (hPipe == lwp.INVALID_HANDLE_VALUE) then
        print("Error: invalid handle")
        return
    else
        print("Created.")
    end

    --TODO: WaitNamedPipe
    local ret = true
    if not ret then
        print("Error: connect failed")
        close(hPipe)
        return
    else
        print("Connected.")
    end

    local lpBytesRead = lwp.newPDWORD(0)
    local lpTotalBytesAvail = lwp.newPDWORD(0)
    local lpBytesLeftThisMessage = lwp.newPDWORD(0)

    while true do
        local instr = io.read("*line")
        while instr:len() > 0 do
            local buf = lwp.toBuffer(instr)
            ret = lwp.WriteFile(hPipe, buf, instr:len(), lpBytesRead, nil)
            local len = lwp.getPDWORD(lpBytesRead)
            print("write: " .. tostring(len))
            if not ret then
                print("Error: write failed")
                close(hPipe)
                return
            end
            instr = instr.sub(len + 1, instr:len())
        end

        while true do
            ret = lwp.PeekNamedPipe(hPipe, nil, 0, lpBytesRead, lpTotalBytesAvail, lpBytesLeftThisMessage)
            print("peek: " ..
                    tostring(lwp.getPDWORD(lpBytesRead)) .. " " ..
                    tostring(lwp.getPDWORD(lpTotalBytesAvail)) .. " " ..
                    tostring(lwp.getPDWORD(lpBytesLeftThisMessage)))
            if not ret then
                print("Error: peek failed")
                close(hPipe)
                return
            end
            local len = lwp.getPDWORD(lpTotalBytesAvail)
            if len == 0 then
                break
            end
            local buf = lwp.newBuffer(len)
            ret = lwp.ReadFile(hPipe, buf, len, lpBytesRead, nil)
            local done = lwp.getPDWORD(lpBytesRead)
            print("read: " .. tostring(done))
            if not ret then
                print("Error: read failed")
                close(hPipe)
                return
            end
            io.write("answer: ", lwp.getBuffer(buf, done), "\n")
        end
    end

    print("Closing pipe.")
    close(hPipe)
end

function close(hPipe)
    local ret = lwp.CloseHandle(hPipe)
    if not ret then
        print("Error: pipe close failed")
    end
end

main()
