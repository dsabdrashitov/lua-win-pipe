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

Release v.1.0 binaries built with _mingw-w64_ for Lua 5.3: [zip][binary]

[sample-client]: sample-client.lua
[sample-server]: sample-server.lua
[binary]:https://github.com/dsabdrashitov/lua-win-pipe/releases/download/v.1.0/lua-win-pipe.zip
