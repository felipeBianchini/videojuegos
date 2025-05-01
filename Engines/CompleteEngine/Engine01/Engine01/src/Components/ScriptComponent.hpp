#ifndef SCRIPTCOMPONENT_HPP 
#define SCRIPTCOMPONENT_HPP

#include <sol/sol.hpp>

struct ScriptComponent {
	sol::function update;
	sol::function onClick;
	sol::function updateBullets;

	ScriptComponent(sol::function update = sol::lua_nil, sol::function onClick = sol::lua_nil, sol::function updateBullets = sol::lua_nil) {
		this->update = update;
		this->onClick = onClick;
		this->updateBullets = updateBullets;
	}
};


#endif // !SCRIPTCOMPONENT_HPP