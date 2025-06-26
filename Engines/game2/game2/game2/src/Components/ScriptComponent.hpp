#ifndef SCRIPTCOMPONENT_HPP 
#define SCRIPTCOMPONENT_HPP

#include <sol/sol.hpp>

struct ScriptComponent {
	sol::function update;
	sol::function onCollision;
	sol::function onClick;
	sol::function enemy_pig_update;

	ScriptComponent(sol::function onCollision = sol::lua_nil, sol::function update = sol::lua_nil, sol::function onClick = sol::lua_nil,
		sol::function enemy_pig_update = sol::lua_nil) {
		this->update = update;
		this->onClick = onClick;
		this->onCollision = onCollision;
		this->enemy_pig_update = enemy_pig_update;
	}
};


#endif // !SCRIPTCOMPONENT_HPP