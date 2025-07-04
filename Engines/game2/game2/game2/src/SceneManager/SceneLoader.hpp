/**
 * @file SceneLoader.hpp
 * @brief Scene loading system for parsing and loading game scenes from configuration files
 */

#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP
#include <string>
#include <memory>
#include <sol/sol.hpp>
#include <tinyxml/tinyxml2.h>
#include <SDL2/SDL.h>
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
#include "../Components/CameraFollowComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../AnimationManager/AnimationManager.hpp"
#include "../Components/CounterComponent.hpp"
#include "../ECS/ECS.hpp"

/**
 * @class SceneLoader
 * @brief Handles loading and parsing of game scenes from configuration files
 * 
 * The SceneLoader class is responsible for parsing scene configuration files
 * (typically Lua scripts) and loading all scene elements including sprites,
 * entities, maps, audio, and other assets into the appropriate game systems.
 */
class SceneLoader {
private:
    /**
     * @brief Loads sprite assets from Lua configuration
     * @param renderer SDL renderer for creating textures
     * @param sprites Lua table containing sprite configuration data
     * @param assetManager Reference to the AssetManager for storing loaded sprites
     */
    void LoadSprites(SDL_Renderer* renderer, const sol::table& sprites, std::unique_ptr<AssetManager>& assetManager);
    
    /**
     * @brief Loads key bindings from Lua configuration
     * @param keys Lua table containing key binding configuration data
     * @param controllerManager Reference to the ControllerManager for storing key bindings
     */
    void LoadKeys(const sol::table& keys, std::unique_ptr<ControllerManager>& controllerManager);
    
    /**
     * @brief Loads game entities from Lua configuration
     * @param lua Reference to the Lua state
     * @param entities Lua table containing entity configuration data
     * @param registry Reference to the ECS Registry for creating entities
     */
    void LoadEntities(sol::state& lua, const sol::table& entities, std::unique_ptr<Registry>& registry);
    
    /**
     * @brief Loads font assets from Lua configuration
     * @param fonts Lua table containing font configuration data
     * @param assetManager Reference to the AssetManager for storing loaded fonts
     */
    void LoadFonts(const sol::table& fonts, std::unique_ptr<AssetManager>& assetManager);
    
    /**
     * @brief Loads button configurations from Lua configuration
     * @param buttons Lua table containing button configuration data
     * @param controllerManager Reference to the ControllerManager for storing button configurations
     */
    void LoadButtons(const sol::table& buttons, std::unique_ptr<ControllerManager>& controllerManager);
    
    /**
     * @brief Loads map data from Lua configuration
     * @param map Lua table containing map configuration data
     * @param registry Reference to the ECS Registry for creating map entities
     */
    void LoadMap(const sol::table map, std::unique_ptr<Registry>& registry);
    
    /**
     * @brief Loads a specific map layer from XML data
     * @param registry Reference to the ECS Registry for creating tile entities
     * @param layer XML element containing layer data
     * @param tileWidth Width of individual tiles in pixels
     * @param tileHeigth Height of individual tiles in pixels
     * @param mapWidth Width of the map in tiles
     * @param columns Number of columns in the tileset
     * @param tileSet Name of the tileset to use
     */
    void LoadLayer(std::unique_ptr<Registry>& registry, tinyxml2::XMLElement* layer, int tileWidth, int tileHeigth, int mapWidth, int columns, const std::string& tileSet);
    
    /**
     * @brief Loads collision objects from XML object group
     * @param registry Reference to the ECS Registry for creating collider entities
     * @param objectGroup XML element containing object group data with collision information
     */
    void LoadColliders(std::unique_ptr<Registry>& registry, tinyxml2::XMLElement* objectGroup);
    
    /**
     * @brief Loads animation data from Lua configuration
     * @param animations Lua table containing animation configuration data
     * @param animationManager Reference to the AnimationManager for storing animation data
     */
    void LoadAnimations(const sol::table& animations, std::unique_ptr<AnimationManager>& animationManager);
    
    /**
     * @brief Loads sound effect assets into the AssetManager
     * @param soundEffects The Lua table containing sound effect configuration data
     * @param assetManager A unique pointer to the AssetManager for storing loaded sound effects
     */
    void LoadSoundEffects(const sol::table& soundEffects, std::unique_ptr<AssetManager>& assetManager);
    
    /**
     * @brief Loads background music assets into the AssetManager
     * @param backgroundMusic The Lua table containing background music configuration data
     * @param assetManager A unique pointer to the AssetManager for storing loaded background music
     */
    void LoadBackgroundMusic(const sol::table& backgroundMusic, std::unique_ptr<AssetManager>& assetManager);
    
    /**
     * @brief Loads background image entities from Lua configuration
     * @param backgroundImages Lua table containing background image configuration data
     * @param registry Reference to the ECS Registry for creating background image entities
     */
    void LoadBackgroundImage(const sol::table& backgroundImages, std::unique_ptr<Registry>& registry);
    
public:
    /**
     * @brief Constructor for SceneLoader
     */
    SceneLoader();
    
    /**
     * @brief Destructor for SceneLoader
     */
    ~SceneLoader();
    
    /**
     * @brief Main method to load a complete scene from a configuration file
     * @param scenePath Path to the scene configuration file
     * @param lua Reference to the Lua state for script execution
     * @param renderer SDL renderer for creating graphical assets
     * @param animationManager Reference to the AnimationManager for animation data
     * @param assetManager Reference to the AssetManager for asset storage
     * @param controllerManager Reference to the ControllerManager for input handling
     * @param registry Reference to the ECS Registry for entity management
     * 
     * This method orchestrates the loading of all scene elements by parsing the
     * configuration file and calling the appropriate specialized loading methods.
     */
    void LoadScene(const std::string& scenePath,
                   sol::state& lua, SDL_Renderer* renderer,
                   std::unique_ptr<AnimationManager>& animationManager,
                   std::unique_ptr<AssetManager>& assetManager,
                   std::unique_ptr<ControllerManager>& controllerManager,
                   std::unique_ptr<Registry>& registry
    );
};

#endif // !SCENELOADER_HPP