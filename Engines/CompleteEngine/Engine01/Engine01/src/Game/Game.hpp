#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <glm/glm.hpp>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <memory>

#include "../ECS/ECS.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../EventManager/EventManager.hpp"

const int FPS = 40;
const int MILISECS_PER_FRAME = 1000 / FPS;

class Game {
public:
	static Game& GetInstance();
	void Init();
	void Run();
	void Destroy();

private:
	Game();
	~Game();
	void Setup();
	void Create();
	void ProcessInput();
	void Update();
	void Render();

	SDL_Window* window;
	SDL_Renderer* renderer;

	bool isRunning;
	int window_width;
	int window_height;

	int millisecsPreviousFrame = 0;

	std::unique_ptr<Registry> registry;

	std::unique_ptr<AssetManager> assetManager;

	std::unique_ptr<EventManager> eventManager;
};

#endif // !GAME_HPP
