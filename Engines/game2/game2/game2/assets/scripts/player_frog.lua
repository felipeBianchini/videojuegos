player_can_jump = false
player_jump_force = -1500.0 * 64.0
player_speed = 3.0 * 64.0

function update()
	local x_vel, y_vel = get_velocity(this)
	x_vel = 0
		if is_action_activated("jump") then
			if player_can_jump then
				add_force(this, 0, player_jump_force)
			end
		end
		if is_action_activated("left") then
			x_vel = x_vel - player_speed
		end
		if is_action_activated("right") then
			x_vel = x_vel + player_speed
		end
		set_velocity(this, x_vel, y_vel)
		player_can_jump = false
end

function on_collision(other)
	if get_tag(other) == "floor" then
		local x_vel, y_vel = get_velocity(this)
		if y_vel == 0 then
			player_can_jump = true
		end
	end
end