local spawnTimer = 0
local spawnInterval = 3

function createEnemy1(dt, wH, wW)
    spawnTimer = spawnTimer + dt
    if spawnTimer >= spawnInterval then
        enemy1Factory(wH, wW)
        spawnTimer = 0
    end
end