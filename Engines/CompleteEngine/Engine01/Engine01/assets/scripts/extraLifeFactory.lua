local spawnTimer = 0
local spawnInterval = 1

function createExtraLife(dt, wH, wW)
    spawnTimer = spawnTimer + dt
    if spawnTimer >= spawnInterval then
        extraLifeFactory(wH, wW)
        spawnTimer = 0
    end
end
