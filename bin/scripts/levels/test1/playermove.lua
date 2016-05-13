b = map:getWorldTime() - lastEventTime
print(b)

if b > 300 and progress == 0 then
    level:updateInformation('first!')
    lastEventTime = map:getWorldTime()
    progress = 1
elseif b > 100 and progress == 1 then
    level:updateInformation('second!')
    progress = 2
end