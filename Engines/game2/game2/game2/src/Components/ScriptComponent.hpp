#ifndef SCRIPTCOMPONENT_HPP 
#define SCRIPTCOMPONENT_HPP

#include <sol/sol.hpp>

struct ScriptComponent {
	sol::function update;
	sol::function onCollision;
	sol::function onClick;

	ScriptComponent(sol::function onCollision = sol::lua_nil, sol::function update = sol::lua_nil, sol::function onClick = sol::lua_nil) {
		this->update = update;
		this->onClick = onClick;
		this->onCollision = onCollision;
	}
};


#endif // !SCRIPTCOMPONENT_HPP