#ifndef SCRIPTCOMPONENT_HPP 
#define SCRIPTCOMPONENT_HPP

#include <sol/sol.hpp>

struct ScriptComponent {
	sol::function update;
	sol::function onClick;
	sol::function updateBullets;
	sol::function updateEnemy1Position;
	sol::function updateEnemy3Position;
	sol::function createEnemy1;
	sol::function createEnemy2;
	sol::function createEnemy3;
	sol::function createExtraLife;
	sol::function bossMechanics;
	sol::function createNuke;

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