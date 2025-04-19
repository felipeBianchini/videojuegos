#ifndef SCRIPTCOMPONENT_HPP 
#define SCRIPTCOMPONENT_HPP

#include <sol/sol.hpp>

struct ScriptComponent {
	sol::function update;

	ScriptComponent(sol::function update = sol::lua_nil) {
		this->update = update;
	}
};


#endif // !SCRIPTCOMPONENT_HPP