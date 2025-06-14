#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include <map>
#include <memory>
#include <string>
#include <sol/sol.hpp>
#include <unordered_map>

#include "SceneLoader.hpp"

/**
 * @class SceneManager
 * @brief A class for managing game scenes and their transitions.
 *
 * This class handles the loading, switching, and tracking of game scenes using Lua scripts.
 * It maintains a collection of scenes, their types, and timers, and provides functionality
 * to control scene execution and transitions.
 */
class SceneManager {
private:
    std::map<std::string, std::string> scenes; ///< Map of scene IDs to their script file paths.
    std::string nextScene;                     ///< The ID of the next scene to load.
    bool isSceneRunning;                       ///< Indicates if a scene is currently running.
    std::unique_ptr<SceneLoader> sceneLoader;  ///< The SceneLoader instance for loading scenes.
    std::unordered_map<std::string, std::string> sceneTypes; ///< Map of scene IDs to their types.
    std::unordered_map<std::string, double> sceneTimers;     ///< Map of scene IDs to their timers.
    std::string currentSceneType;              ///< The type of the currently active scene.
    double currentSceneTimer;                  ///< The timer for the currently active scene.

public:
    /**
     * @brief Constructor for the SceneManager.
     *
     * Initializes the SceneManager with default values and creates a SceneLoader instance.
     */
    SceneManager();

    /**
     * @brief Destructor for the SceneManager.
     *
     * Cleans up resources used by the SceneManager, including the SceneLoader.
     */
    ~SceneManager();

    /**
     * @brief Loads a scene configuration from a Lua script.
     *
     * Reads the specified Lua script to configure a scene and stores its details for later use.
     *
     * @param path The file path to the Lua script containing the scene configuration.
     * @param lua The Lua state for executing the scene script.
     */
    void LoadSceneFromScript(const std::string& path, sol::state& lua);

    /**
     * @brief Loads the next scene using the SceneLoader.
     *
     * Triggers the loading of the scene designated as the next scene.
     */
    void LoadScene();

    /**
     * @brief Gets the ID of the next scene to be loaded.
     *
     * @return The ID of the next scene.
     */
    std::string GetNextScene() const;

    /**
     * @brief Sets the ID of the next scene to be loaded.
     *
     * @param nextScene The ID of the next scene.
     */
    void SetNextScene(const std::string& nextScene);

    /**
     * @brief Checks if a scene is currently running.
     *
     * @return True if a scene is running, false otherwise.
     */
    bool IsSceneRunning() const;

    /**
     * @brief Starts the current scene.
     *
     * Sets the scene running state to true.
     */
    void StartScene();

    /**
     * @brief Stops the current scene.
     *
     * Sets the scene running state to false.
     */
    void StopScene();

    /**
     * @brief Gets the type of the currently active scene.
     *
     * @return The type of the current scene.
     */
    std::string GetCurrentSceneType();

    /**
     * @brief Gets the timer for the currently active scene.
     *
     * @return The timer value for the current scene.
     */
    double GetCurrentSceneTimer();
};

#endif // !SCENEMANAGER_HPP