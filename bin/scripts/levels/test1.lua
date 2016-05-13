mapLoader = TiledTxtMapLoader.new(level, 'test_map')
map = mapLoader:loadMap();
level:setMap(map)

player = map:getEntityPlayer(-1)
player:setX(6)
player:setY(4)
player:setOnInitScript('playerinit')
player:setOnMoveScript('playermove')

print(map:getWidth())
c = EntityGlassDebris.new(level)
c:setX(6)
c:setY(8)
map:addEntity(c)

d = EntityToaster.new(level)
d:setX(6)
d:setY(10)
map:addEntity(d)