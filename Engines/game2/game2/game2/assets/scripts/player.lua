player_states = {
	idle = 1,
	run = 2,
	jump = 3,
	fall = 4,
}
player_state = player_states["idle"]
player_can_jump = false
player_jump_force = -2000.0 * 64.0
player_ladder_velocity = -128.0
player_on_ladder = false
player_speed = 3.0 * 64.0
jump_multiplier = 2.0

function update()
	local x_vel, y_vel = get_velocity(this)
	x_vel = 0
	local final_y_vel = y_vel

	if is_action_activated("jump") then
		if player_can_jump then
			play_soundEffect("player_jump", 75)
			add_force(this, 0, player_jump_force)
		end
	end

	if is_action_activated("left") then
		x_vel = x_vel - player_speed
	end
	if is_action_activated("right") then
		x_vel = x_vel + player_speed
	end

	if player_on_ladder and is_action_activated("up") then
		final_y_vel = player_ladder_velocity
	end

	if is_action_activated("run") then
		x_vel = x_vel * jump_multiplier
	end
	if is_action_activated("restart") then
		kill_player();
	end
	if is_action_activated("menu") then
		go_to_scene("main_menu");
	end

	set_velocity(this, x_vel, final_y_vel)

	player_can_jump = false
	player_on_ladder = false
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
		play_soundEffect("boing", 75)
		add_force(this, 0, player_jump_force * 2.5)
    elseif tag == "goal" then
		play_soundEffect("win", 90)
        go_to_scene("main_menu")
    elseif tag == "deadly_obstacle" then
		kill_player();
		--player_death(this)
	elseif tag == "enemy_pig" or tag == "enemy_bird" then
		if left_collision(this, other) or right_collision(this, other) then
			--player_death(this)
			kill_player();
		elseif bottom_collision(this, other) then
			if is_action_activated("jump") then
				add_force(this, 0, player_jump_force);
			else
				add_force(this, 0, player_jump_force * 0.5);
			end
		end
	elseif tag == "enemy_turtle" then
        local x_vel, y_vel = get_velocity(this)
        if y_vel == 0 then
            player_can_jump = true
        end
	elseif tag == "ladder" then
		player_on_ladder = true
    end
end

function player_death(entity)
	play_soundEffect("player_hurt", 75)
	set_position(entity, 16, 3000)
end

function update_animation_state()
	local x_vel, y_vel = get_velocity(this)
	if -0.001 < x_vel and x_vel < 0.001 then
		if player_state ~= player_states["idle"] then
			player_state = player_states["idle"]
			change_animation(this, "player_idle")
		end
	end
	if x_vel >= 0.001 then
		flip_sprite(this, false)
		if player_state ~= player_states["run"] then
			player_state = player_states["run"]
			change_animation(this, "player_run")
		end
	end
	if x_vel <= -0.001 then
		flip_sprite(this, true)
		if player_state ~= player_states["run"] then
			player_state = player_states["run"]
			change_animation(this, "player_run")
		end
	end
	if y_vel <= -0.001 then
		if player_state ~= player_states["jump"] then
			player_state = player_states["jump"]
			change_animation(this, "player_jump")
		end
	end
	if y_vel >= 0.001 then
		if player_state ~= player_states["fall"] then
			player_state = player_states["fall"]
			change_animation(this, "player_fall")
		end
	end
end