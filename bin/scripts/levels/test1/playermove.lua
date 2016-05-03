if b == nil then b = 0 end
b = b + 1
print(b)

if b > 100 then level:updateInformation('first!') end
if b > 200 then level:updateInformation('second!') end