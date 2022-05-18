-- Change path
local prev_path = package.path
local root_path = debug.getinfo(1).source:match("@(.*\\)") or ""
package.path = root_path .. "?.lua"

-- imports and libs
lwp = require("build.lua-win-pipe.lua-win-pipe")

-- Restore path
package.path = prev_path

PIPE_NAME = "\\\\.\\pipe\\lwp_test"
PIPE_OUT_BUFFER_SIZE = 32
PIPE_IN_BUFFER_SIZE = 32
--READ_BUFFER_SIZE = 10
--WRITE_BUFFER_SIZE = 10
READ_BUFFER_SIZE = 100
WRITE_BUFFER_SIZE = 100

function main()
    local hPipe = lwp.CreateNamedPipe(
            PIPE_NAME,
            lwp.PIPE_ACCESS_DUPLEX,
            lwp.mask(lwp.PIPE_TYPE_BYTE, lwp.PIPE_READMODE_BYTE, lwp.PIPE_WAIT),
            lwp.PIPE_UNLIMITED_INSTANCES,
            PIPE_OUT_BUFFER_SIZE,
            PIPE_IN_BUFFER_SIZE,
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
    if (not ret) and (lwp.GetLastError() ~= lwp.ERROR_PIPE_CONNECTED) then
        print("Error: connect failed (" .. tostring(lwp.GetLastError()) .. ")")
        close(hPipe)
        return
    else
        print("Connected.")
    end

    local readBuffer = lwp.newBuffer(READ_BUFFER_SIZE)
    local writeBuffer = lwp.newBuffer(WRITE_BUFFER_SIZE)
    local pdwBytesDone = lwp.newPDWORD(0)
    local pdwTotalBytesAvail = lwp.newPDWORD(0)
    local pdwBytesLeftThisMessage = lwp.newPDWORD(0)

    local lastprint = nil
    while true do
        local readParts = {}
        while (true) do
            ret = lwp.PeekNamedPipe(hPipe, nil, 0, pdwBytesDone, pdwTotalBytesAvail, pdwBytesLeftThisMessage)
            local toprint = "peek: " ..
                    tostring(lwp.getPDWORD(pdwBytesDone)) .. " " ..
                    tostring(lwp.getPDWORD(pdwTotalBytesAvail)) .. " " ..
                    tostring(lwp.getPDWORD(pdwBytesLeftThisMessage))
            if toprint ~= lastprint then
                print(toprint)
                lastprint = toprint
            end
            if not ret then
                print("Error: peek failed (" .. tostring(lwp.GetLastError()) .. ")")
                goto end_main_loop
            end
            if lwp.getPDWORD(pdwTotalBytesAvail) == 0 then
                goto end_read_loop
            end
            ret = lwp.ReadFile(hPipe, readBuffer, READ_BUFFER_SIZE, pdwBytesDone, nil)
            print("read: " .. tostring(lwp.getPDWORD(pdwBytesDone)))
            if not ret then
                print("Error: read failed (" .. tostring(lwp.GetLastError()) .. ")")
                goto end_main_loop
            end
            local readPart = lwp.fromBuffer(readBuffer, lwp.getPDWORD(pdwBytesDone))
            readParts[#readParts + 1] = readPart
        end
        ::end_read_loop::
        local readMessage = table.concat(readParts)

        if readMessage == "" then
            goto continue_main_loop
        end

        local replyMessage = "this is reply to '" .. readMessage .. "'"
        for i = 1, replyMessage:len(), WRITE_BUFFER_SIZE do
            local cnt = math.min(replyMessage:len() - i + 1, WRITE_BUFFER_SIZE)
            lwp.toBuffer(writeBuffer, replyMessage:sub(i, i + cnt - 1))
            ret = lwp.WriteFile(hPipe, writeBuffer, cnt, pdwBytesDone, nil)
            print("write: " .. tostring(lwp.getPDWORD(pdwBytesDone)))
            if not ret then
                print("Error: write failed (" .. tostring(lwp.GetLastError()) .. ")")
                goto end_main_loop
            end
        end

        ::continue_main_loop::
    end
    ::end_main_loop::

    print("Closing pipe.")
    close(hPipe)
end

function close(hPipe)
    local ret = lwp.CloseHandle(hPipe)
    if not ret then
        print("Error: pipe close failed (" .. tostring(lwp.GetLastError()) .. ")")
    end
end

main()
