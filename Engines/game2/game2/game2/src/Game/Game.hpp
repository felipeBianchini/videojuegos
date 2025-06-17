#ifndef GAME_HPP
#define GAME_HPP
#
#include <SDL.h>
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

const int FPS = 40;
const int MILISECS_PER_FRAME = 1000 / FPS;

class Game {
private:
	Game();
	~Game();
	void Setup();
	void Create();
	void RunScene();
	void ProcessInput();
	void Update();
	void Render();

	SDL_Window* window;

	SDL_Rect camera = { 0,0,0,0 };

	bool isRunning;
	bool isDebugMode = false;

	int millisecsPreviousFrame = 0;
public:
	int window_width = 0;
	int window_height = 0;

	int mapHeigth = 0;
	int mapWidth = 0;
	SDL_Renderer* renderer;
	sol::state lua;
	std::unique_ptr<AssetManager> assetManager;
	std::unique_ptr<EventManager> eventManager;
	std::unique_ptr<ControllerManager> controllerManager;
	std::unique_ptr<Registry> registry;
	std::unique_ptr<SceneManager> sceneManager;


	static Game& GetInstance();
	void Init();
	void Run();
	void Destroy();
};

#endif // !GAME_HPP
