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
		lua.set_function("enemy1Factory", Enemy1Factory);
		lua.set_function("enemy2Factory", Enemy2Factory);
		lua.set_function("enemyBulletsFactory", EnemyBulletsFactory);
	}

	void Update(sol::state& lua, double dt, int wH, int wW) {
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
			else if (script.createEnemy1 != sol::lua_nil) {
				script.createEnemy1(dt, wH, wW);
			}
			else if (script.updateEnemy1Position != sol::lua_nil) {
				TransformComponent transform = entity.GetComponent<TransformComponent>();
				double enemyX = transform.position.x;
				double enemyY = transform.position.y;
				script.updateEnemy1Position(dt, enemyX, enemyY);
			}
			else if (script.createEnemy2 != sol::lua_nil) {
				script.createEnemy2(dt, wH, wW);
			}
		}
	}
};

#endif // !SCRIPTSYSTEM_HPP