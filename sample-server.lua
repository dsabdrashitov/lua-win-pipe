-- Change path
local prev_path = package.path
local root_path = debug.getinfo(1).source:match("@(.*\\)") or ""
package.path = root_path .. "?.lua"

-- imports and libs
lwp = require("build.lua-win-pipe.lua-win-pipe")

-- Restore path
package.path = prev_path

function main()
    local hPipe = lwp.CreateNamedPipe(
            "\\\\.\\pipe\\lwp_test",
            lwp.PIPE_ACCESS_DUPLEX,
            lwp.mask(lwp.PIPE_TYPE_BYTE, lwp.PIPE_READMODE_BYTE, lwp.PIPE_WAIT),
            lwp.PIPE_UNLIMITED_INSTANCES,
            32,
            32,
            1000,
            nil
    )

    if (hPipe == lwp.INVALID_HANDLE_VALUE) then
        print("Error: invalid handle")
        return
    else
        print("Created.")
    end

    local ret = lwp.ConnectNamedPipe(hPipe, nil)
    if not ret then
        -- Need to check also for ERROR_PIPE_CONNECTED but have no GetLastError yet
        print("Error: connect failed")
        close(hPipe)
        return
    else
        print("Connected.")
    end

    local bufsize = 10
    local buf = lwp.newBuffer(bufsize)
    local lpBytesRead = lwp.newPDWORD(0)
    local lpTotalBytesAvail = lwp.newPDWORD(0)
    local lpBytesLeftThisMessage = lwp.newPDWORD(0)

    local replysize = 5

    while true do
        ret = lwp.PeekNamedPipe(hPipe, buf, 0, lpBytesRead, lpTotalBytesAvail, lpBytesLeftThisMessage)
        print("peek: " ..
                tostring(lwp.getPDWORD(lpBytesRead)) .. " " ..
                tostring(lwp.getPDWORD(lpTotalBytesAvail)) .. " " ..
                tostring(lwp.getPDWORD(lpBytesLeftThisMessage)))
        if not ret then
            print("Error: peek failed")
            break
        end
        ret = lwp.ReadFile(hPipe, buf, bufsize, lpBytesRead, nil)
        local len = lwp.getPDWORD(lpBytesRead)
        print("read: " .. tostring(len))
        if not ret then
            print("Error: read failed")
            break
        end
        local message = lwp.getBuffer(buf, len)
        print("message: '" .. message .. "'")
        local reply = "this is reply to '" .. message .. "'"
        for i = 1, message:len(), replysize do
            local cnt = math.min(message:len() - i + 1, replysize)
            local reply = lwp.toBuffer(reply:sub(i, cnt))
            ret = lwp.WriteFile(hPipe, reply, cnt, lpBytesRead, nil)
            len = lwp.getPDWORD(lpBytesRead)
            print("write: " .. tostring(len))
            if not ret then
                print("Error: write failed")
                close(hPipe)
                return
            end
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
