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
		lua.set_function("is_action_activated", IsActionActivated);
	}

	void Update() {
		for (auto entity :  GetSystemEntiities()) {
			const auto& script = entity.GetComponent<ScriptComponent>();
			if (script.update != sol::lua_nil) {
				script.update();
			}
		}
	}
};

#endif // !SCRIPTSYSTEM_HPP