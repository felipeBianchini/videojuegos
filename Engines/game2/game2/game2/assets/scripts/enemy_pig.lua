enemy_states = {
	idle = 1,
	walk = 2,
	hit = 3,
}
enemy_state = enemy_states["idle"]
enemy_speed = 1.0 * 64.0
enemy_direction = -1 

function enemy_pig_update(dt)
	local _, y_vel = get_velocity(this)
	local x_vel = enemy_direction * enemy_speed
	set_velocity(this, x_vel, y_vel)
	update_pig_animation_state()
end

function on_collision(other)
	local tag = get_tag(other)
	if tag == "obstacle" then
		enemy_direction = -enemy_direction
	end
end

function update_pig_animation_state()
	local x_vel, y_vel = get_velocity(this)

	if -0.001 < x_vel and x_vel < 0.001 then
		if enemy_state ~= enemy_states["idle"] then
			enemy_state = enemy_states["idle"]
			change_animation(this, "enemy_pig_idle")
		end
	end

	if x_vel > 0.001 then
		flip_sprite(this, false)
		if enemy_state ~= enemy_states["walk"] then
			enemy_state = enemy_states["walk"]
			change_animation(this, "enemy_pig_walk")
		end
	elseif x_vel < -0.001 then
		flip_sprite(this, true)
		if enemy_state ~= enemy_states["walk"] then
			enemy_state = enemy_states["walk"]
			change_animation(this, "enemy_pig_walk")
		end
	end

	if y_vel <= -0.001 then
		if enemy_state ~= enemy_states["hit"] then
			enemy_state = enemy_states["hit"]
			change_animation(this, "enemy_pig_hit")
		end
	end
end
