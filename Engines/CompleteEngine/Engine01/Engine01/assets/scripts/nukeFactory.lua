local spawnTimer = 0
local spawnInterval = 35

function createNuke(dt, wH, wW)
    spawnTimer = spawnTimer + dt
    if spawnTimer >= spawnInterval then
        nukeFactory(wH, wW)
        spawnTimer = 0
    end
end
