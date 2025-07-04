/**
 * @file SceneManager.hpp
 * @brief Scene management system for handling scene transitions and lifecycle
 */

#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP
#include <map>
#include <memory>
#include <string>
#include <sol/sol.hpp>
#include "SceneLoader.hpp"

/**
 * @class SceneManager
 * @brief Manages scene transitions and lifecycle in the game
 * 
 * The SceneManager class handles the loading, starting, stopping, and transitioning
 * between different game scenes. It maintains a registry of available scenes and
 * manages the current scene state. Works in conjunction with SceneLoader to
 * actually load scene data from configuration files.
 */
class SceneManager {
private:
    /**
     * @brief Map of scene names to their corresponding file paths
     * 
     * Stores the mapping between scene identifiers and their configuration
     * file paths for easy scene lookup and loading.
     */
    std::map<std::string, std::string> scenes;
    
    /**
     * @brief Name of the next scene to be loaded
     * 
     * Stores the identifier of the scene that should be loaded next,
     * used for scene transitions.
     */
    std::string nextScene;
    
    /**
     * @brief Flag indicating if a scene is currently running
     * 
     * Tracks whether the current scene is active and running or if
     * the game is in a transitional state.
     */
    bool isSceneRunning = false;
    
    /**
     * @brief Scene loader instance for loading scene data
     * 
     * Handles the actual loading of scene configuration files and
     * populating game systems with scene data.
     */
    std::unique_ptr<SceneLoader> sceneLoader;
    
public:
    /**
     * @brief Constructor for SceneManager
     * 
     * Initializes the scene manager and creates the scene loader instance.
     */
    SceneManager();
    
    /**
     * @brief Destructor for SceneManager
     * 
     * Cleans up scene manager resources and the scene loader.
     */
    ~SceneManager();
    
    /**
     * @brief Loads scene configuration from a Lua script file
     * @param path File path to the scene configuration script
     * @param lua Reference to the Lua state for script execution
     * 
     * Executes the specified Lua script to load scene configuration data
     * and register available scenes with their file paths.
     */
    void LoadSceneFromScript(const std::string& path, sol::state& lua);
    
    /**
     * @brief Loads the next scheduled scene
     * 
     * Initiates the loading process for the scene specified in nextScene.
     * This method coordinates with the SceneLoader to actually load all
     * scene assets and entities.
     */
    void LoadScene();
    
    /**
     * @brief Gets the name of the next scene to be loaded
     * @return String containing the next scene identifier
     */
    std::string GetNextScene() const;
    
    /**
     * @brief Sets the next scene to be loaded
     * @param nextScene String identifier of the scene to load next
     * 
     * Schedules a scene transition by setting which scene should be
     * loaded when LoadScene() is called.
     */
    void SetNextScene(const std::string& nextScene);
    
    /**
     * @brief Checks if a scene is currently running
     * @return True if a scene is currently active, false otherwise
     */
    bool IsSceneRunning() const;
    
    /**
     * @brief Starts the current scene
     * 
     * Marks the current scene as running and active. This typically
     * happens after a scene has been successfully loaded.
     */
    void StartScene();
    
    /**
     * @brief Stops the current scene
     * 
     * Marks the current scene as not running, typically done before
     * transitioning to a new scene or when pausing the game.
     */
    void StopScene();
};

#endif // !SCENEMANAGER_HPP