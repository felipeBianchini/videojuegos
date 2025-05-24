local spawnTimer = 0
local spawnInterval = 15

function createExtraLife(dt, wH, wW)
    spawnTimer = spawnTimer + dt
    if spawnTimer >= spawnInterval then
        extraLifeFactory(wH, wW)
        spawnTimer = 0
    end
end
