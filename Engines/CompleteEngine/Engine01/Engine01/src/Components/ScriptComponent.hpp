#ifndef SCRIPTCOMPONENT_HPP 
#define SCRIPTCOMPONENT_HPP

#include <sol/sol.hpp>

/**
 * @brief Component that holds Lua script functions for game logic.
 *
 * This component stores various Lua functions that can be bound to
 * entity behavior, such as updating, clicking, enemy spawning, and boss mechanics.
 */
struct ScriptComponent {
	sol::function update;                ///< Lua function called every frame to update the entity.
	sol::function onClick;               ///< Lua function called when the entity is clicked.
	sol::function updateBullets;         ///< Lua function to update bullet behavior.
	sol::function updateEnemy1Position; ///< Lua function to update position of enemy type 1.
	sol::function updateEnemy3Position; ///< Lua function to update position of enemy type 3.
	sol::function createEnemy1;          ///< Lua function to spawn enemy type 1.
	sol::function createEnemy2;          ///< Lua function to spawn enemy type 2.
	sol::function createEnemy3;          ///< Lua function to spawn enemy type 3.
	sol::function createExtraLife;       ///< Lua function to create an extra life power-up.
	sol::function bossMechanics;         ///< Lua function controlling boss-specific mechanics.
	sol::function createNuke;            ///< Lua function to create a nuke or special attack.

	/**
	 * @brief Constructs a ScriptComponent with optional Lua functions.
	 *
	 * @param update Lua update function, defaults to nil.
	 * @param onClick Lua onClick function, defaults to nil.
	 * @param updateBullets Lua function for updating bullets, defaults to nil.
	 * @param updateEnemy1Position Lua function for enemy 1 position update, defaults to nil.
	 * @param createEnemy1 Lua function to spawn enemy 1, defaults to nil.
	 * @param createEnemy2 Lua function to spawn enemy 2, defaults to nil.
	 * @param createEnemy3 Lua function to spawn enemy 3, defaults to nil.
	 * @param createExtraLife Lua function to spawn extra life, defaults to nil.
	 * @param updateEnemy3Position Lua function for enemy 3 position update, defaults to nil.
	 * @param bossMechanics Lua function for boss mechanics, defaults to nil.
	 * @param createNuke Lua function to spawn nuke, defaults to nil.
	 */
	ScriptComponent(sol::function update = sol::lua_nil, sol::function onClick = sol::lua_nil,
		sol::function updateBullets = sol::lua_nil, sol::function updateEnemy1Position = sol::lua_nil,
		sol::function createEnemy1 = sol::lua_nil, sol::function createEnemy2 = sol::lua_nil,
		sol::function createEnemy3 = sol::lua_nil, sol::function createExtraLife = sol::lua_nil,
		sol::function updateEnemy3Position = sol::lua_nil, sol::function bossMechanics = sol::lua_nil,
		sol::function createNuke = sol::lua_nil) {
		this->update = update;
		this->onClick = onClick;
		this->updateBullets = updateBullets;
		this->updateEnemy1Position = updateEnemy1Position;
		this->createEnemy1 = createEnemy1;
		this->createEnemy2 = createEnemy2;
		this->createEnemy3 = createEnemy3;
		this->createExtraLife = createExtraLife;
		this->updateEnemy3Position = updateEnemy3Position;
		this->bossMechanics = bossMechanics;
		this->createNuke = createNuke;
	}
};


#endif // !SCRIPTCOMPONENT_HPP