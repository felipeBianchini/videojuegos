-- Variables globales
player_velocity = 200;

fixed_player_velocity = math.sqrt((player_velocity * player_velocity) / 2);

function update()
	set_velocity(this, 0, 0);
	vel_x = 0;
	vel_y = 0;
	if is_action_activated("up") then
		vel_y = vel_y + -1;
	end
	if is_action_activated("left") then
		vel_x = vel_x + -1;
	end	
	if is_action_activated("down") then
		vel_y = vel_y + 1;
	end	
	if is_action_activated("right") then
		vel_x = vel_x + 1;
	end	

	if vel_x ~= 0 and vel_y ~= 0 then
		vel_x = vel_x * fixed_player_velocity;
		vel_y = vel_y * fixed_player_velocity;
	else
		vel_x = vel_x * player_velocity;
		vel_y = vel_y * player_velocity;
	end

	set_velocity(this, vel_x, vel_y);

end

local shootTimer = 0
local shootInterval = 1

function shootBullet(playerX, playerY)
	print("shootBullet")
	bulletFactory(playerX, playerY)
end

function updateBullets(dt, playerX, playerY)
	print("updateBullets")
    shootTimer = shootTimer + dt

    if shootTimer >= shootInterval then
        shootBullet(playerX, playerY)
        shootTimer = 0
    end
end
