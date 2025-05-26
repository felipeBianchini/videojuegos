local phase = 1
local hasShield = true

local phaseTimer = 0
local ringTimer = 0
local aimTimer = 0
local spreadTimer = 0

local bulletSpeed = 300

local ringInterval = 3
local aimInterval = 1.5
local spreadInterval = 2.5
local waveInterval = 25

function spreadGroupShoot(posX, posY)
    local numBullets = 12
    local offsetX = 100
    local offsetY = 175
    local spawnX = posX + offsetX
    local spawnY = posY + offsetY

    local baseAngle = math.random(45, 180)

    for i = 1, numBullets do
        local spreadFactor = (i - (numBullets / 2)) / (numBullets / 2)
        local angle = baseAngle + spreadFactor * 10
        local rad = math.rad(angle)
        local dx = math.cos(rad)
        local dy = math.sin(rad)
        local vx = dx * bulletSpeed + spreadFactor * 450
        local vy = dy * bulletSpeed

        bossAttack(vx, vy, spawnX, spawnY)
    end
end

function ringShoot(posX, posY)
    local numBullets = 16
    for i = 0, numBullets - 1 do
        local angle = i * (360 / numBullets)
        local rad = math.rad(angle)
        local dirX = math.cos(rad)
        local dirY = math.sin(rad)
        local offsetX = 100
        local offsetY = 175
        bossAttack(dirX * bulletSpeed, dirY * bulletSpeed, posX + offsetX, posY + offsetY)
    end
end

function aimAtPlayer(posX, posY, playerX, playerY)
    local offsetX = 100
    local offsetY = 175
    local newPosX = posX + offsetX
    local newPosY = posY + offsetY
    local dx = playerX - newPosX
    local dy = playerY - newPosY
    local len = math.sqrt(dx * dx + dy * dy)
    if len > 0 then
        dx = dx / len
        dy = dy / len
        bossAttack(dx * bulletSpeed, dy * bulletSpeed, newPosX, newPosY)
    end
end

function bossMechanics(dt, wH, wW, posX, posY, playerX, playerY)
    if phase == 1 then
        phaseTimer = phaseTimer + dt
        ringTimer = ringTimer + dt
        aimTimer = aimTimer + dt
        spreadTimer = spreadTimer + dt

        if spreadTimer >= spreadInterval then
            spreadGroupShoot(posX, posY)
            spreadTimer = 0
        end

        if ringTimer >= ringInterval then
            ringShoot(posX, posY)
            ringTimer = 0
        end

        if aimTimer >= aimInterval then
            aimAtPlayer(posX, posY, playerX, playerY)
            aimTimer = 0
        end

        if phaseTimer >= waveInterval then
            phase = 2
            print("Cambio a Fase 2")
            phaseTimer = 0
            ringTimer = 0
            aimTimer = 0
            spreadTimer = 0
        end

    elseif phase == 2 then
        for i = 1, 3 do
            enemy1Factory(wH, wW)
            enemy2Factory(wH, wW)
            enemy3Factory(wH, wW)        
        end
        phase = 3
        print("Cambio a Fase 3")
        phaseTimer = 0

    elseif phase == 3 then
        phaseTimer = phaseTimer + dt
        removeShield()
        hasShield = false
        if phaseTimer >= waveInterval then
            phase = 1
            print("Escudo eliminado. Boss vulnerable.")
            phaseTimer = 0
            ringTimer = 0
            aimTimer = 0
            spreadTimer = 0
        end
    end
end
