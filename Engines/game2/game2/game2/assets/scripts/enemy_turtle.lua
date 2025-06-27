turtle_states = {
	spikes_in = 1,
	spikes_out = 2,
	transitioning_in = 3,
	transitioning_out = 4,
}

local turtle_state = turtle_states["spikes_in"]
local timer = 0.0
local wait_duration = 4.0
local transition_duration = 8 / 15 

function enemy_turtle_update(dt)
	timer = timer + dt

	if turtle_state == turtle_states["spikes_in"] and timer >= wait_duration then
		change_animation(this, "enemy_turtle_spikes_out")
		turtle_state = turtle_states["transitioning_out"]
		timer = 0.0

	elseif turtle_state == turtle_states["transitioning_out"] then
		if timer >= transition_duration then
			change_animation(this, "enemy_turtle_idle_spikes_out")
			turtle_state = turtle_states["spikes_out"]
			timer = 0.0
		end

	elseif turtle_state == turtle_states["spikes_out"] and timer >= wait_duration then
		change_animation(this, "enemy_turtle_spikes_in")
		turtle_state = turtle_states["transitioning_in"]
		timer = 0.0

	elseif turtle_state == turtle_states["transitioning_in"] then
		if timer >= transition_duration then
			change_animation(this, "enemy_turtle_idle_spikes_in")
			turtle_state = turtle_states["spikes_in"]
			timer = 0.0
		end
	end
end

function on_collision(other)
    local tag = get_tag(other)
    if tag == "player" and top_collision(this, other) and (turtle_state == turtle_states["spikes_out"] or turtle_state == turtle_states["transitioning_out"]) then
		player_death(other)
    end
end