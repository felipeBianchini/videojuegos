local flying_up = true
local timer = 0.0
local direction_duration = 2.0
local bird_speed = 200.0

function enemy_bird_update(dt)
    timer = timer + dt

    local x, y = get_position(this)

    if flying_up then
        y = y + bird_speed * dt
    else
        y = y - bird_speed * dt
    end

    set_position(this, x, y)

    if timer >= direction_duration then
        flying_up = not flying_up
        timer = 0.0
    end
end

function on_collision(other)
    local tag = get_tag(other)
    if tag == "player" and top_collision(this, other) then
		enemy_bird_is_dying()
    end
end

function enemy_bird_is_dying()
	change_animation(this, "enemy_bird_hit")
	kill_entity(this)
end