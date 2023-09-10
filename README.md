# lua-win-pipe
Library wraps some set of functions which allow using windows named pipes
in synchronous mode (no wrapper for Overlapped structure).

Implemented functions:
- ConnectNamedPipe
- CloseHandle
- CreateFile
- CreateNamedPipe
- GetLastError
- PeekNamedPipe
- ReadFile
- WaitNamedPipe
- WriteFile

Example of using the wrappers is given in files
[sample-client.lua][sample-client] and [sample-server.lua][sample-server].

Release v.1.1 binaries built with _mingw-w64_ for Lua 5.3: [zip][binary-lua53]

Release v.1.1 binaries built with _mingw-w64_ for Lua 5.4: [zip][binary-lua54]

[sample-client]: sample-client.lua
[sample-server]: sample-server.lua
[binary-lua53]:https://github.com/dsabdrashitov/lua-win-pipe/releases/download/v.1.1/lua-win-pipe-v_1_1-lua53-win64.zip
[binary-lua54]:https://github.com/dsabdrashitov/lua-win-pipe/releases/download/v.1.1/lua-win-pipe-v_1_1-lua54-win64.zip