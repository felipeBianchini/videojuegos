player_states = {
	idle = 1,
	run = 2,
	jump = 3,
	fall = 4,
}
player_state = player_states["idle"]
player_can_jump = false
player_jump_force = -1200.0 * 64.0
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
		update_animation_state()
end

function on_collision(other)
    local tag = get_tag(other)
    if tag == "floor" or tag == "obstacle" then
        local x_vel, y_vel = get_velocity(this)
        if y_vel == 0 then
            player_can_jump = true
        end
	elseif tag == "mushroom" then
		add_force(this, 0, player_jump_force * 2.5)
    elseif tag == "goal" then
        go_to_scene("victory")
    elseif tag == "deadly_obstacle" then
        go_to_scene("defeat")
    end
end

function update_animation_state()
	local x_vel, y_vel = get_velocity(this)
	-- no se mueve
	if -0.001 < x_vel and x_vel < 0.001 then
		if player_state ~= player_states["idle"] then
			player_state = player_states["idle"]
			change_animation(this, "player_frog_idle")
		end
	end
	-- derecha
	if x_vel >= 0.001 then
		flip_sprite(this, false)
		if player_state ~= player_states["run"] then
			player_state = player_states["run"]
			change_animation(this, "player_frog_run")
		end
	end
	-- izquierda
	if x_vel <= -0.001 then
		flip_sprite(this, true)
		if player_state ~= player_states["run"] then
			player_state = player_states["run"]
			change_animation(this, "player_frog_run")
		end
	end
	-- salta
	if y_vel <= -0.001 then
		if player_state ~= player_states["jump"] then
			player_state = player_states["jump"]
			change_animation(this, "player_frog_jump")
		end
	end
	-- cae
	if y_vel >= 0.001 then
		if player_state ~= player_states["fall"] then
			player_state = player_states["fall"]
			change_animation(this, "player_frog_fall")
		end
	end
end