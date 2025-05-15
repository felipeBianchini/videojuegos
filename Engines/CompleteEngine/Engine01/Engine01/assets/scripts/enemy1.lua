local shootTimer = 0
local shootInterval = 1

function enemy1_Attack(enemyX, enemyY)
	enemyBulletsFactory(enemyX, enemyY)
end

function updateEnemy1Position(dt, enemyX, enemyY)
    shootTimer = shootTimer + dt
    if shootTimer >= shootInterval then
        enemy1_Attack(enemyX, enemyY)
        shootTimer = 0
    end
end