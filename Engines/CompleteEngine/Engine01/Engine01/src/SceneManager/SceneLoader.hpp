#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include <string>
#include <memory>
#include <sol/sol.hpp>
#include <SDL.h>

#include "../AssetManager/AssetManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"

#include "../Components/TransformComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/ClickableComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/ScoreComponent.hpp"
#include "../Components/EntityTypeComponent.hpp"
#include "../Components/IsEntityInsideTheScreenComponent.hpp"

#include "../ECS/ECS.hpp"

/**
 * @class SceneLoader
 * @brief A class for loading game scenes from Lua configuration files.
 * 
 * This class is responsible for loading and initializing game assets, entities, and input configurations
 * for a scene using Lua scripts. It interacts with the AssetManager, ControllerManager, and ECS Registry
 * to set up sprites, fonts, buttons, backgrounds, sound effects, background music, and entities.
 */
class SceneLoader {
private:
    /**
     * @brief Loads sprite assets into the AssetManager.
     * 
     * Processes the sprite table from the Lua configuration and loads the corresponding textures
     * into the AssetManager for use in rendering.
     * 
     * @param renderer The SDL renderer used for texture creation.
     * @param sprites The Lua table containing sprite configuration data.
     * @param assetManager A unique pointer to the AssetManager for storing loaded sprites.
     */
    void LoadSprites(SDL_Renderer* renderer, const sol::table& sprites, std::unique_ptr<AssetManager>& assetManager);

    /**
     * @brief Loads key bindings into the ControllerManager.
     * 
     * Processes the keys table from the Lua configuration and registers key bindings with the ControllerManager.
     * 
     * @param keys The Lua table containing key binding configuration data.
     * @param controllerManager A unique pointer to the ControllerManager for registering key bindings.
     */
    void LoadKeys(const sol::table& keys, std::unique_ptr<ControllerManager>& controllerManager);

    /**
     * @brief Loads entities into the ECS Registry.
     * 
     * Processes the entities table from the Lua configuration and creates entities with their respective
     * components in the ECS Registry.
     * 
     * @param lua The Lua state for accessing script data.
     * @param entities The Lua table containing entity configuration data.
     * @param registry A unique pointer to the ECS Registry for creating entities.
     */
    void LoadEntities(sol::state& lua, const sol::table& entities, std::unique_ptr<Registry>& registry);

    /**
     * @brief Loads font assets into the AssetManager.
     * 
     * Processes the fonts table from the Lua configuration and loads the corresponding font assets
     * into the AssetManager.
     * 
     * @param fonts The Lua table containing font configuration data.
     * @param assetManager A unique pointer to the AssetManager for storing loaded fonts.
     */
    void LoadFonts(const sol::table& fonts, std::unique_ptr<AssetManager>& assetManager);

    /**
     * @brief Loads button configurations into the ControllerManager.
     * 
     * Processes the buttons table from the Lua configuration and registers button input mappings
     * with the ControllerManager.
     * 
     * @param buttons The Lua table containing button configuration data.
     * @param controllerManager A unique pointer to the ControllerManager for registering button mappings.
     */
    void LoadButtons(const sol::table& buttons, std::unique_ptr<ControllerManager>& controllerManager);

    /**
     * @brief Loads background assets into the AssetManager.
     * 
     * Processes the backgrounds table from the Lua configuration and loads the corresponding background
     * textures into the AssetManager.
     * 
     * @param renderer The SDL renderer used for texture creation.
     * @param backgrounds The Lua table containing background configuration data.
     * @param assetManager A unique pointer to the AssetManager for storing loaded backgrounds.
     */
    void LoadBackgrounds(SDL_Renderer* renderer, const sol::table& backgrounds, std::unique_ptr<AssetManager>& assetManager);

    /**
     * @brief Loads sound effect assets into the AssetManager.
     * 
     * Processes the sound effects table from the Lua configuration and loads the corresponding sound
     * effects into the AssetManager.
     * 
     * @param soundEffects The Lua table containing sound effect configuration data.
     * @param assetManager A unique pointer to the AssetManager for storing loaded sound effects.
     */
    void LoadSoundEffects(const sol::table& soundEffects, std::unique_ptr<AssetManager>& assetManager);

    /**
     * @brief Loads background music assets into the AssetManager.
     * 
     * Processes the background music table from the Lua configuration and loads the corresponding
     * background music into the AssetManager.
     * 
     * @param backgroundMusic The Lua table containing background music configuration data.
     * @param assetManager A unique pointer to the AssetManager for storing loaded background music.
     */
    void LoadBackgroundMusic(const sol::table& backgroundMusic, std::unique_ptr<AssetManager>& assetManager);

public:
    /**
     * @brief Constructor for the SceneLoader.
     * 
     * Initializes the SceneLoader instance.
     */
    SceneLoader();

    /**
     * @brief Destructor for the SceneLoader.
     * 
     * Cleans up any resources used by the SceneLoader.
     */
    ~SceneLoader();

    /**
     * @brief Loads a scene from a Lua configuration file.
     * 
     * Reads the specified Lua script file and initializes the game scene by loading sprites, fonts,
     * buttons, backgrounds, sound effects, background music, and entities into the provided managers
     * and registry.
     * 
     * @param scenePath The file path to the Lua script containing the scene configuration.
     * @param lua The Lua state for executing the scene script.
     * @param renderer The SDL renderer used for texture creation.
     * @param assetManager A unique pointer to the AssetManager for storing loaded assets.
     * @param controllerManager A unique pointer to the ControllerManager for registering input mappings.
     * @param registry A unique pointer to the ECS Registry for creating entities.
     */
    void LoadScene(const std::string& scenePath,
        sol::state& lua, SDL_Renderer* renderer,
        std::unique_ptr<AssetManager>& assetManager,
        std::unique_ptr<ControllerManager>& controllerManager,
        std::unique_ptr<Registry>& registry
    );
};

#endif // !SCENELOADER_HPP