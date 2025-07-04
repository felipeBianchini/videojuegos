/**
 * @file ScriptSystem.hpp
 * @brief System for managing and executing Lua scripts on entities
 */

#ifndef SCRIPTSYSTEM_HPP
#define SCRIPTSYSTEM_HPP
#include <memory>
#include <sol/sol.hpp>
#include "../Components/ScriptComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Binding/LuaBinding.hpp"

/**
 * @class ScriptSystem
 * @brief System responsible for executing Lua scripts attached to entities
 * 
 * This system handles the execution of Lua scripts for entities that have
 * ScriptComponent. It provides Lua bindings for ECS functionality and executes
 * different types of update functions based on the script type (general update,
 * enemy-specific updates, etc.).
 */
class ScriptSystem : public System {
public:
    /**
     * @brief Constructor for ScriptSystem
     * 
     * Initializes the script system and sets up the required component types.
     * Only entities with ScriptComponent will be processed by this system.
     */
    ScriptSystem() {
        RequiredComponent<ScriptComponent>();
    }
    
    /**
     * @brief Creates Lua bindings for ECS functionality
     * 
     * Sets up the Lua environment with bindings to C++ functions and classes,
     * allowing Lua scripts to interact with the ECS system. This includes
     * entity manipulation, input handling, physics operations, and game state
     * management functions.
     * 
     * @param lua Lua state to bind functions and types to
     */
    void CreateLuaBinding(sol::state& lua) {
        // Classes
        lua.new_usertype<Entity>("entity");
        
        // Functions
        lua.set_function("is_action_activated", IsActionActivated);
        lua.set_function("set_velocity", SetVelocity);
        lua.set_function("go_to_scene", GoToScene);
        lua.set_function("get_tag", GetTag);
        lua.set_function("left_collision", LeftCollision);
        lua.set_function("right_collision", RightCollision);
        lua.set_function("bottom_collision", BottomCollision);
        lua.set_function("top_collision", TopCollision);
        lua.set_function("get_position", GetPosition);
        lua.set_function("set_position", SetPosition);
        lua.set_function("get_size", GetSize);
        lua.set_function("get_velocity", GetVelocity);
        lua.set_function("add_force", AddForce);
        lua.set_function("change_animation", ChangeAnimation);
        lua.set_function("flip_sprite", FlipSprite);
        lua.set_function("play_soundEffect", PlaySoundEffect);
        lua.set_function("kill_entity", KillEntity);
        lua.set_function("kill_player", PlayerKilled);
        lua.set_function("next_level", NextLevel);
    }
    
    /**
     * @brief Updates all script components by executing their Lua functions
     * 
     * Iterates through all entities with ScriptComponent and executes their
     * appropriate update functions. The system checks for different types of
     * update functions in priority order: general update, enemy pig update,
     * enemy turtle update, and enemy bird update. Sets the "this" variable
     * in Lua to the current entity before execution.
     * 
     * @param lua Lua state for script execution
     * @param dt Delta time since last update (in seconds)
     */
    void Update(sol::state& lua, double dt) {
        for (auto entity : GetSystemEntiities()) {
            const auto& script = entity.GetComponent<ScriptComponent>();
            
            // Execute general update function if available
            if (script.update != sol::lua_nil) {
                lua["this"] = entity;
                script.update();
            }
            // Execute enemy pig-specific update function
            else if (script.enemy_pig_update != sol::lua_nil) {
                lua["this"] = entity;
                script.enemy_pig_update(dt);
            }
            // Execute enemy turtle-specific update function
            else if (script.enemy_turtle_update != sol::lua_nil) {
                lua["this"] = entity;
                script.enemy_turtle_update(dt);
            }
            // Execute enemy bird-specific update function
            else if (script.enemy_bird_update != sol::lua_nil) {
                lua["this"] = entity;
                script.enemy_bird_update(dt);
            }
        }
    }
};
#endif // !SCRIPTSYSTEM_HPP