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
		lua.set_function("go_to_nextScene", GoToNextScene);
		lua.set_function("bulletFactory", BulletFactory);
	}

	void Update(sol::state& lua, double dt) {
		for (auto entity :  GetSystemEntiities()) {
			const auto& script = entity.GetComponent<ScriptComponent>();
			if (script.update != sol::lua_nil && script.updateBullets != sol::lua_nil) {
				lua["this"] = entity;
				TransformComponent transform = entity.GetComponent<TransformComponent>();
				double playerX = transform.position.x;
				double playerY = transform.position.y;
				script.update();
				script.updateBullets(dt, playerX, playerY);
			}
		}
	}
};

#endif // !SCRIPTSYSTEM_HPP