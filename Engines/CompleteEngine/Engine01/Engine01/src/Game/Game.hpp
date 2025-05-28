#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <SDL_mixer.h>
#include <glm/glm.hpp>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sol/sol.hpp>

#include <memory>

#include "../ECS/ECS.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../EventManager/EventManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../SceneManager/SceneManager.hpp"

/**
 * @brief The target frames per second for the game loop.
 */
const int FPS = 40;

/**
 * @brief The number of milliseconds per frame, calculated as 1000 / FPS.
 */
const int MILISECS_PER_FRAME = 1000 / FPS;

/**
 * @class Game
 * @brief The main game class responsible for initializing and running the game.
 *
 * This class manages the game loop, SDL resources, and core systems such as the ECS Registry,
 * AssetManager, EventManager, ControllerManager, and SceneManager. It uses a singleton pattern
 * to ensure a single instance of the game.
 */
class Game {
private:
    /**
     * @brief Private constructor for the Game class (singleton pattern).
     *
     * Initializes the game instance.
     */
    Game();

    /**
     * @brief Destructor for the Game class.
     *
     * Cleans up resources used by the game.
     */
    ~Game();

    /**
     * @brief Sets up initial game resources and systems.
     *
     * Initializes SDL, Lua, and other core components.
     */
    void Setup();

    /**
     * @brief Creates the initial game state.
     *
     * Sets up the ECS systems and initial entities.
     */
    void Create();

    /**
     * @brief Runs the current scene.
     *
     * Handles scene-specific logic and updates.
     */
    void RunScene();

    /**
     * @brief Processes user input.
     *
     * Handles input events through the ControllerManager.
     */
    void ProcessInput();

    /**
     * @brief Updates the game state.
     *
     * Updates all ECS systems and game logic based on the time delta.
     */
    void Update();

    /**
     * @brief Renders the game frame.
     *
     * Draws all renderable components to the screen using the SDL renderer.
     */
    void Render();

    SDL_Window* window;                        ///< The SDL window for the game.
    bool isRunning;                            ///< Indicates if the game loop is running.
    bool keepRunning;                          ///< Indicates if the game should continue running.
    int millisecsPreviousFrame;                ///< The timestamp of the previous frame for delta time calculation.

public:
    int window_width;                          ///< The width of the game window.
    int window_height;                         ///< The height of the game window.
    SDL_Renderer* renderer;                    ///< The SDL renderer for drawing graphics.
    sol::state lua;                            ///< The Lua state for scripting.
    std::unique_ptr<AssetManager> assetManager; ///< Manages game assets like textures and sounds.
    std::unique_ptr<EventManager> eventManager; ///< Manages game events and notifications.
    std::unique_ptr<ControllerManager> controllerManager; ///< Manages user input and controls.
    std::unique_ptr<Registry> registry;        ///< The ECS Registry for managing entities and components.
    std::unique_ptr<SceneManager> sceneManager; ///< Manages game scenes and transitions.

    /**
     * @brief Gets the singleton instance of the Game class.
     *
     * @return A reference to the single Game instance.
     */
    static Game& GetInstance();

    /**
     * @brief Initializes the game.
     *
     * Sets up SDL, creates the window and renderer, and initializes all core systems.
     */
    void Init();

    /**
     * @brief Runs the main game loop.
     *
     * Executes the game loop, processing input, updating state, and rendering frames until the game is stopped.
     */
    void Run();

    /**
     * @brief Destroys the game and cleans up resources.
     *
     * Frees SDL resources and shuts down the game.
     */
    void Destroy();
};

#endif // !GAME_HPP