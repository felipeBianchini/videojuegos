local spawnTimer = 0
local spawnInterval = 4

function createEnemy2(dt, wH, wW)
    spawnTimer = spawnTimer + dt
    if spawnTimer >= spawnInterval then
        enemy2Factory(wH, wW)
        spawnTimer = 0
    end
end