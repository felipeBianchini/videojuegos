#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <glm/glm.hpp>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <memory>

#include "../ECS/ECS.hpp"

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

	std::unique_ptr<Registry> registry;

};

#endif // !GAME_HPP
