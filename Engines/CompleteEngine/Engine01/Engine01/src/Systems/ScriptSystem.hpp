#ifndef SCRIPTSYSTEM_HPP
#define SCRIPTSYSTEM_HPP

#include <memory>
#include <sol/sol.hpp>

#include "../Components/ScriptComponent.hpp"
#include "../Game/Game.hpp"
#include "../ECS/ECS.hpp"
#include "../Binding/LuaBinding.hpp"

/**
 * @class ScriptSystem
 * @brief A system for managing Lua script execution within an Entity-Component-System (ECS) architecture.
 *
 * This system handles entities with a ScriptComponent, binding Lua functions and updating entity behaviors
 * based on Lua scripts for various game mechanics such as player movement, enemy creation, and boss behavior.
 */
class ScriptSystem : public System {
public:
	/**
	 * @brief Constructor for the ScriptSystem.
	 *
	 * Initializes the system and specifies that entities must have a ScriptComponent to be managed.
	 */
	ScriptSystem() {
		RequiredComponent<ScriptComponent>();
	}
	/**
	 * @brief Creates Lua bindings for the system.
	 *
	 * Registers the Entity class and various game-related functions to the Lua state for scripting purposes.
	 *
	 * @param lua The Lua state to bind functions and classes to.
	 */
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
		lua.set_function("enemy3Factory", Enemy3Factory);
		lua.set_function("extraLifeFactory", ExtraLifeFactory);
		lua.set_function("enemy3BulletsFactory", Enemy3Attack);
		lua.set_function("bossAttack", BossAttack);
		lua.set_function("nukeFactory", NukeFactory);
		lua.set_function("checkBossHealth", CheckBossHealth);
	}
	/**
	 * @brief Updates entities with script components based on their Lua scripts.
	 *
	 * Iterates through managed entities, executing their associated Lua script functions
	 * for updates, enemy creation, and other game mechanics, depending on the script's capabilities.
	 *
	 * @param lua The Lua state used for script execution.
	 * @param dt Delta time since the last update, used for time-based calculations.
	 * @param wH The height of the game window.
	 * @param wW The width of the game window.
	 */
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
			else if (script.createEnemy3 != sol::lua_nil) {
				script.createEnemy3(dt, wH, wW);
			}
			else if (script.createExtraLife != sol::lua_nil) {
				script.createExtraLife(dt, wH, wW);
			}
			else if (script.updateEnemy3Position != sol::lua_nil) {
				TransformComponent transform = entity.GetComponent<TransformComponent>();
				double enemyX = transform.position.x;
				double enemyY = transform.position.y;
				script.updateEnemy3Position(dt, enemyX, enemyY);
			}
			else if (script.bossMechanics != sol::lua_nil) {
				Entity player = Game::GetInstance().registry->GetSystem<GameManagerSystem>().GetPlayer();
				TransformComponent transformPlayer = player.GetComponent<TransformComponent>();
				double playerX = transformPlayer.position.x;
				double playerY = transformPlayer.position.y;
				TransformComponent transform = entity.GetComponent<TransformComponent>();
				double bossX = transform.position.x;
				double bossY = transform.position.y;
				script.bossMechanics(dt, wH, wW, bossX, bossY, playerX, playerY);
			}
			else if (script.createNuke != sol::lua_nil) {
				script.createNuke(dt, wH, wW);
			}
		}
	}
};

#endif // !SCRIPTSYSTEM_HPP