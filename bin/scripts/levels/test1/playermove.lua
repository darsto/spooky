if a == nil then a = map:getWorldTime() end
b = map:getWorldTime() - a
print(b)

if b > 100 then level:updateInformation('first!') end
if b > 200 then level:updateInformation('second!') end