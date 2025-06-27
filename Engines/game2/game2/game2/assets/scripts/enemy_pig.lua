pig_states = {
	idle = 1,
	walk = 2,
	hit = 3,
}

local pig_state = pig_states["idle"]
pig_speed = 1.0 * 64.0
local pig_direction = 1
local pig_timer = 0.0
pig_move_duration = 3.0

function enemy_pig_update(dt)
	local x_vel, y_vel = get_velocity(this)
	pig_timer = pig_timer + dt
	if pig_timer >= pig_move_duration then
		pig_direction = -pig_direction
		pig_timer = 0.0
	end
	local x_vel = pig_direction * pig_speed
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
		if pig_state ~= pig_states["walk"] then
			pig_state = pig_states["walk"]
			change_animation(this, "enemy_pig_walk")
		end
	elseif x_vel > -0.001 then
		flip_sprite(this, true)
		if pig_state ~= pig_states["walk"] then
			pig_state = pig_states["walk"]
			change_animation(this, "enemy_pig_walk")
		end
	end
end

function enemy_pig_is_dying()
	change_animation(this, "enemy_pig_hit")
	kill_entity(this)
end
