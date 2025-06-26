enemy_states = {
	idle = 1,
	walk = 2,
	hit = 3,
}

enemy_state = enemy_states["idle"]
enemy_speed = 1.0 * 64.0
enemy_direction = 1
enemy_timer = 0.0
enemy_move_duration = 3.0

function enemy_pig_update(dt)
	local x_vel, y_vel = get_velocity(this)
	enemy_timer = enemy_timer + dt
	if enemy_timer >= enemy_move_duration then
		enemy_direction = -enemy_direction
		enemy_timer = 0.0
	end
	local x_vel = enemy_direction * enemy_speed
	set_velocity(this, x_vel, y_vel)
	update_pig_animation_state()
end

function on_collision(other)
    local tag = get_tag(other)
    if tag == "player" and top_collision(this, other) then
		enemy_pig_is_dying()
    end
end

function update_pig_animation_state()
	local x_vel, y_vel = get_velocity(this)
	if x_vel < 0.001 then
		flip_sprite(this, false)
		if enemy_state ~= enemy_states["walk"] then
			enemy_state = enemy_states["walk"]
			change_animation(this, "enemy_pig_walk")
		end
	elseif x_vel > -0.001 then
		flip_sprite(this, true)
		if enemy_state ~= enemy_states["walk"] then
			enemy_state = enemy_states["walk"]
			change_animation(this, "enemy_pig_walk")
		end
	end
end

function enemy_pig_is_dying()
	change_animation(this, "enemy_pig_hit")
	kill_entity(this)
end
