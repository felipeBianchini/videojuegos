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
		lua.set_function("get_position", GetPosition);
		lua.set_function("set_position", SetPosition);
		lua.set_function("get_size", GetSize);
		lua.set_function("get_velocity", GetVelocity);
		lua.set_function("add_force", AddForce);
	}

	void Update(sol::state& lua) {
		for (auto entity :  GetSystemEntiities()) {
			const auto& script = entity.GetComponent<ScriptComponent>();
			if (script.update != sol::lua_nil) {
				lua["this"] = entity;
				script.update();
			}
		}
	}
};

#endif // !SCRIPTSYSTEM_HPP