local winpipe = require("winpipe")
message(winpipe.somefunc())
for name, val in pairs(winpipe.constants()) do
    message(name .. ": " .. val)
end