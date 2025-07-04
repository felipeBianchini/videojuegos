#ifndef SCRIPTSYSTEM_HPP
#define SCRIPTSYSTEM_HPP

#include <memory>
#include <sol/sol.hpp>

#include "../Components/ScriptComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Binding/LuaBinding.hpp"

class ScriptSystem : public System {
public:
	ScriptSystem() {
		RequiredComponent<ScriptComponent>();
	}

	void CreateLuaBinding(sol::state& lua) {
		// Classes
		lua.new_usertype<Entity>("entity");

		// Functions
		lua.set_function("is_action_activated", IsActionActivated);
		lua.set_function("set_velocity", SetVelocity);
		lua.set_function("go_to_scene", GoToScene);
		lua.set_function("get_tag", GetTag);
		lua.set_function("left_collision", LeftCollision);
		lua.set_function("right_collision", RightCollision);
		lua.set_function("bottom_collision", BottomCollision);
		lua.set_function("top_collision", TopCollision);
		lua.set_function("get_position", GetPosition);
		lua.set_function("set_position", SetPosition);
		lua.set_function("get_size", GetSize);
		lua.set_function("get_velocity", GetVelocity);
		lua.set_function("add_force", AddForce);
		lua.set_function("change_animation", ChangeAnimation);
		lua.set_function("flip_sprite", FlipSprite);
		lua.set_function("play_soundEffect", PlaySoundEffect);
		lua.set_function("kill_entity", KillEntity);
		lua.set_function("kill_player", PlayerKilled);
		lua.set_function("next_level", NextLevel);
	}

	void Update(sol::state& lua, double dt) {
		for (auto entity :  GetSystemEntiities()) {
			const auto& script = entity.GetComponent<ScriptComponent>();
			if (script.update != sol::lua_nil) {
				lua["this"] = entity;
				script.update();
			}
			else if (script.enemy_pig_update != sol::lua_nil) {
				lua["this"] = entity;
				script.enemy_pig_update(dt);
			}
			else if (script.enemy_turtle_update != sol::lua_nil) {
				lua["this"] = entity;
				script.enemy_turtle_update(dt);
			}
			else if (script.enemy_bird_update != sol::lua_nil) {
				lua["this"] = entity;
				script.enemy_bird_update(dt);
			}
		}
	}
};

#endif // !SCRIPTSYSTEM_HPP