local spawnTimer = 0
local spawnInterval = 45

function createNuke(dt, wH, wW)
    spawnTimer = spawnTimer + dt
    if spawnTimer >= spawnInterval then
        nukeFactory(wH, wW)
        spawnTimer = 0
    end
end
