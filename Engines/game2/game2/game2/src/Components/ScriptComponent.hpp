/**
 * @file ScriptComponent.hpp
 * @brief Component for attaching Lua scripts to entities
 */

#ifndef SCRIPTCOMPONENT_HPP
#define SCRIPTCOMPONENT_HPP
#include <sol/sol.hpp>

/**
 * @struct ScriptComponent
 * @brief Component that enables entities to execute Lua scripts for behavior
 * 
 * This component allows entities to have custom behavior defined in Lua scripts.
 * It stores function references for common game events like updates, collisions,
 * and clicks, as well as specific enemy behavior functions. The scripting system
 * provides flexibility for game logic without requiring C++ recompilation.
 */
struct ScriptComponent {
    sol::function update;              ///< Lua function called every frame for general updates
    sol::function onCollision;         ///< Lua function called when collision events occur
    sol::function onClick;             ///< Lua function called when entity is clicked
    sol::function enemy_pig_update;    ///< Lua function for pig enemy-specific update behavior
    sol::function enemy_turtle_update; ///< Lua function for turtle enemy-specific update behavior
    sol::function enemy_bird_update;   ///< Lua function for bird enemy-specific update behavior
    
    /**
     * @brief Constructor for ScriptComponent
     * @param onCollision Lua function for collision handling (default: sol::lua_nil)
     * @param update Lua function for frame updates (default: sol::lua_nil)
     * @param onClick Lua function for click handling (default: sol::lua_nil)
     * @param enemy_pig_update Lua function for pig enemy behavior (default: sol::lua_nil)
     * @param enemy_turtle_update Lua function for turtle enemy behavior (default: sol::lua_nil)
     * @param enemy_bird_update Lua function for bird enemy behavior (default: sol::lua_nil)
     * 
     * All parameters default to sol::lua_nil, meaning no script function is assigned.
     * Functions can be set individually as needed for the specific entity's behavior.
     * The scripting system will only call functions that are not nil.
     */
    ScriptComponent(sol::function onCollision = sol::lua_nil, sol::function update = sol::lua_nil, sol::function onClick = sol::lua_nil,
                    sol::function enemy_pig_update = sol::lua_nil, sol::function enemy_turtle_update = sol::lua_nil, sol::function enemy_bird_update = sol::lua_nil) {
        this->update = update;
        this->onClick = onClick;
        this->onCollision = onCollision;
        this->enemy_pig_update = enemy_pig_update;
        this->enemy_turtle_update = enemy_turtle_update;
        this->enemy_bird_update = enemy_bird_update;
    }
};

#endif // !SCRIPTCOMPONENT_HPP