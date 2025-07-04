/**
 * @file Game.hpp
 * @brief Main game class implementing the singleton pattern for game loop management
 */

#ifndef GAME_HPP
#define GAME_HPP
#
#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <SDL2/SDL_ttf.h>
#include <sol/sol.hpp>
#include <memory>
#include "../ECS/ECS.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../EventManager/EventManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../SceneManager/SceneManager.hpp"
#include "../AnimationManager/AnimationManager.hpp"

/**
 * @brief Target frames per second for the game loop
 */
const int FPS = 40;

/**
 * @brief Milliseconds per frame to maintain target FPS
 */
const int MILISECS_PER_FRAME = 1000 / FPS;

/**
 * @class Game
 * @brief Main game class implementing singleton pattern
 * 
 * Manages the core game loop, SDL initialization, and coordinates all major
 * game systems including ECS, asset management, events, and rendering.
 * Uses the singleton pattern to ensure only one game instance exists.
 */
class Game {
private:
    /**
     * @brief Private constructor for singleton pattern
     */
    Game();
    
    /**
     * @brief Private destructor for singleton pattern
     */
    ~Game();
    
    /**
     * @brief Sets up game systems and initializes components
     */
    void Setup();
    
    /**
     * @brief Creates and initializes game entities and scenes
     */
    void Create();
    
    /**
     * @brief Runs the current scene logic
     */
    void RunScene();
    
    /**
     * @brief Processes input events from SDL
     */
    void ProcessInput();
    
    /**
     * @brief Updates game logic and systems
     */
    void Update();
    
    /**
     * @brief Renders the current frame to the screen
     */
    void Render();
    
    /**
     * @brief Flag indicating if the game is currently paused
     */
    bool isPaused = false;
    
    /**
     * @brief Pointer to the main SDL window
     */
    SDL_Window* window;
    
    /**
     * @brief Camera rectangle defining the viewport
     */
    SDL_Rect camera = { 0,0,0,0 };
    
    /**
     * @brief Flag indicating if the game loop should continue running
     */
    bool isRunning;
    
    /**
     * @brief Flag indicating if debug mode is enabled
     */
    bool isDebugMode = false;
    
    /**
     * @brief Timestamp of the previous frame for delta time calculation
     */
    int millisecsPreviousFrame = 0;
    
public:
    /**
     * @brief Width of the game window in pixels
     */
    int window_width = 0;
    
    /**
     * @brief Height of the game window in pixels
     */
    int window_height = 0;
    
    /**
     * @brief Current number of player deaths
     */
    int currentDeaths = 0;
    
    /**
     * @brief Flag indicating if the game is currently restarting
     */
    bool isRestarting = false;
    
    /**
     * @brief Height of the current map in pixels or tiles
     */
    int mapHeigth = 0;
    
    /**
     * @brief Width of the current map in pixels or tiles
     */
    int mapWidth = 0;
    
    /**
     * @brief Pointer to the main SDL renderer
     */
    SDL_Renderer* renderer;
    
    /**
     * @brief Lua state for scripting support
     */
    sol::state lua;
    
    /**
     * @brief Asset manager for loading and managing game resources
     */
    std::unique_ptr<AssetManager> assetManager;
    
    /**
     * @brief Event manager for handling game events
     */
    std::unique_ptr<EventManager> eventManager;
    
    /**
     * @brief Controller manager for handling input devices
     */
    std::unique_ptr<ControllerManager> controllerManager;
    
    /**
     * @brief ECS registry for managing entities and components
     */
    std::unique_ptr<Registry> registry;
    
    /**
     * @brief Scene manager for handling different game scenes
     */
    std::unique_ptr<SceneManager> sceneManager;
    
    /**
     * @brief Animation manager for handling sprite animations
     */
    std::unique_ptr<AnimationManager> animationManager;
    
    /**
     * @brief Gets the singleton instance of the Game class
     * @return Reference to the single Game instance
     */
    static Game& GetInstance();
    
    /**
     * @brief Initializes the game, SDL, and all subsystems
     */
    void Init();
    
    /**
     * @brief Runs the main game loop
     */
    void Run();
    
    /**
     * @brief Destroys the game and cleans up resources
     */
    void Destroy();
};

#endif // !GAME_HPP