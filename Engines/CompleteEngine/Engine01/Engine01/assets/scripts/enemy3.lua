local shootTimer = 0
local shootInterval = 4

function enemy3_Attack(enemyX, enemyY)
	enemy3BulletsFactory(enemyX, enemyY)
end

function updateEnemy3Position(dt, enemyX, enemyY)
    shootTimer = shootTimer + dt
    if shootTimer >= shootInterval then
        enemy3_Attack(enemyX, enemyY)
        shootTimer = 0
    end
end