-- Change path
local prev_path = package.path
local root_path = debug.getinfo(1).source:match("@(.*\\)") or ""
package.path = root_path .. "?.lua"

-- imports and libs
lwp = require("build.lua-win-pipe.lua-win-pipe")

-- Restore path
package.path = prev_path

PIPE_NAME = "\\\\.\\pipe\\lwp_test"

function main()

    local ret = lwp.WaitNamedPipe(PIPE_NAME, 15000)
    if not ret then
        print("Error: WaitNamedPipe failed (" .. tostring(lwp.GetLastError()) .. ")")
        return
    end

    local hPipe = lwp.CreateFile(
            PIPE_NAME,
            lwp.mask(lwp.GENERIC_READ, lwp.GENERIC_WRITE),
            lwp.FILE_NO_SHARE,
            nil,
            lwp.OPEN_EXISTING,
            lwp.FILE_ATTRIBUTE_DEFAULT,
            nil
    )

    if (hPipe == lwp.INVALID_HANDLE_VALUE) then
        print("Error: invalid handle (" .. tostring(lwp.GetLastError()) .. ")")
        return
    else
        print("Created.")
    end

    local pdwBytesDone = lwp.ByteBlock_alloc(lwp.SIZEOF_DWORD)
    local pdwTotalBytesAvail = lwp.ByteBlock_alloc(lwp.SIZEOF_DWORD)
    local pdwBytesLeftThisMessage = lwp.ByteBlock_alloc(lwp.SIZEOF_DWORD)

    while true do
        local strIn = io.read("*line")
        if strIn == "" then
            print("Can't send empty message")
            goto continue_main_loop
        end
        local writeBuffer = lwp.ByteBlock_alloc(strIn:len())
        lwp.ByteBlock_setString(writeBuffer, strIn)
        ret = lwp.WriteFile(hPipe, writeBuffer, strIn:len(), pdwBytesDone, nil)
        print("write: " .. tostring(lwp.ByteBlock_getDWORD(pdwBytesDone)))
        if (not ret) or (lwp.ByteBlock_getDWORD(pdwBytesDone) ~= strIn:len()) then
            print("Error: write failed (" .. tostring(lwp.GetLastError()) .. ")")
            goto end_main_loop
        end

        -- Answer is not empty so wait some data arrive
        local lastprint = nil
        while true do
            ret = lwp.PeekNamedPipe(hPipe, nil, 0, pdwBytesDone, pdwTotalBytesAvail, pdwBytesLeftThisMessage)
            local toprint = "peek: " ..
                    tostring(lwp.ByteBlock_getDWORD(pdwBytesDone)) .. " " ..
                    tostring(lwp.ByteBlock_getDWORD(pdwTotalBytesAvail)) .. " " ..
                    tostring(lwp.ByteBlock_getDWORD(pdwBytesLeftThisMessage))
            if toprint ~= lastprint then
                print(toprint)
                lastprint = toprint
            end
            if not ret then
                print("Error: peek failed (" .. tostring(lwp.GetLastError()) .. ")")
                goto end_main_loop
            end
            local len = lwp.ByteBlock_getDWORD(pdwTotalBytesAvail)
            if len ~= 0 then
                goto end_wait_loop
            end
        end
        ::end_wait_loop::

        local readParts = {}
        while true do
            ret = lwp.PeekNamedPipe(hPipe, nil, 0, pdwBytesDone, pdwTotalBytesAvail, pdwBytesLeftThisMessage)
            print("peek: " ..
                    tostring(lwp.ByteBlock_getDWORD(pdwBytesDone)) .. " " ..
                    tostring(lwp.ByteBlock_getDWORD(pdwTotalBytesAvail)) .. " " ..
                    tostring(lwp.ByteBlock_getDWORD(pdwBytesLeftThisMessage)))
            if not ret then
                print("Error: peek failed (" .. tostring(lwp.GetLastError()) .. ")")
                goto end_main_loop
            end
            local len = lwp.ByteBlock_getDWORD(pdwTotalBytesAvail)
            if len == 0 then
                goto end_read_loop
            end
            local buf = lwp.ByteBlock_alloc(len)
            ret = lwp.ReadFile(hPipe, buf, len, pdwBytesDone, nil)
            print("read: " .. tostring(lwp.ByteBlock_getDWORD(pdwBytesDone)))
            if not ret then
                print("Error: read failed (" .. tostring(lwp.GetLastError()) .. ")")
                goto end_main_loop
            end
            local readPart = lwp.ByteBlock_getString(buf, lwp.ByteBlock_getDWORD(pdwBytesDone))
            readParts[#readParts + 1] = readPart
        end
        ::end_read_loop::
        local reply = table.concat(readParts)

        print("answer: " .. reply)
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
