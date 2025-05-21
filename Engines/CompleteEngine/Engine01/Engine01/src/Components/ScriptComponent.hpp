#ifndef SCRIPTCOMPONENT_HPP 
#define SCRIPTCOMPONENT_HPP

#include <sol/sol.hpp>

struct ScriptComponent {
	sol::function update;
	sol::function onClick;
	sol::function updateBullets;
	sol::function updateEnemy1Position;
	sol::function createEnemy1;
	sol::function createEnemy2;
	sol::function createEnemy3;
	sol::function createEnemy4;

	ScriptComponent(sol::function update = sol::lua_nil, sol::function onClick = sol::lua_nil,
		sol::function updateBullets = sol::lua_nil, sol::function updateEnemy1Position = sol::lua_nil,
		sol::function createEnemy1 = sol::lua_nil, sol::function createEnemy2 = sol::lua_nil,
		sol::function createEnemy3 = sol::lua_nil, sol::function createEnemy4 = sol::lua_nil) {
		this->update = update;
		this->onClick = onClick;
		this->updateBullets = updateBullets;
		this->updateEnemy1Position = updateEnemy1Position;
		this->createEnemy1 = createEnemy1;
		this->createEnemy2 = createEnemy2;
		this->createEnemy3 = createEnemy3;
		this->createEnemy4 = createEnemy4;
	}
};


#endif // !SCRIPTCOMPONENT_HPP