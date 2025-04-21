#include <iostream>

#include "Game.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/ScriptComponent.hpp"


#include "../Systems/RenderSystem.hpp"
#include "../Systems/MovementSystem.hpp"
#include "../Systems/CollisionSystem.hpp"
#include "../Systems/DamageSystem.hpp"
#include "../Systems/AnimationSystem.hpp"
#include "../Systems/ScriptSystem.hpp"

Game::Game()
{
	this->window = nullptr;
	this->renderer = nullptr;
	this->isRunning = true;
	this->window_width = 800;
	this->window_height = 600;
	this->registry = std::make_unique<Registry>();
	std::cout << "GAME se ejecuta constructor" << std::endl;
	assetManager = std::make_unique<AssetManager>();
	eventManager = std::make_unique<EventManager>();
	controllerManager = std::make_unique<ControllerManager>();
	sceneLoader = std::make_unique<SceneLoader>();
}

Game& Game::GetInstance()
{
	static Game game;
	return game;
}

void Game::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error inicializando SDL!" << std::endl;
	}

	if (TTF_Init() != 0) {
		std::cerr << "Error inicializando TTF!" << std::endl;
		return;
	}
	this->Create();
}

void Game::Create() {
	if ((this->window = SDL_CreateWindow(
		"Game Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		this->window_width,
		this->window_height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	)) == NULL)
	{
		std::cerr << "Error creando ventana!" << std::endl;
		return;
	}

	if ((this->renderer = SDL_CreateRenderer(this->window, -1, 0)) == NULL) {
		std::cerr << "Error creando renderer!" << std::endl;
		return;
	}
}

void Game::Setup()
{
	registry->AddSystem<MovementSystem>();
	registry->AddSystem<RenderSystem>();
	registry->AddSystem<CollisionSystem>();
	registry->AddSystem<DamageSystem>();
	registry->AddSystem<AnimationSystem>();
	registry->AddSystem<ScriptSystem>();

	lua.open_libraries(sol::lib::base, sol::lib::math);
	//lua.script_file("./assets/scripts/player.lua");
	//sol::function update = lua["update"];
	registry->GetSystem<ScriptSystem>().CreateLuaBinding(lua);

	sceneLoader->LoadScene("./assets/scripts/scene_01.lua", lua, renderer, assetManager, controllerManager, registry);

	//assetManager->AddTexture(renderer, "alan", "./assets/images/enemy_alan.png");
	//assetManager->AddTexture(renderer, "crushingCyclops", "./assets/images/CrushingCyclops.png");
	
	//controllerManager->AddActionKey("up", SDLK_w); // keyCode = 119
	//controllerManager->AddActionKey("left", SDLK_a); // keyCode = 97
	//controllerManager->AddActionKey("down", SDLK_s); // keyCode = 115
	//controllerManager->AddActionKey("right", SDLK_d); // keyCode = 100

	//Entity player = this->registry->CreateEntity();
	//player.AddComponent<CircleColliderComponent>(8, 16, 16);
	//player.AddComponent<RigidBodyComponent>(glm::vec2(0, 0));
	//player.AddComponent<ScriptComponent>(update);
	//player.AddComponent<SpriteComponent>("alan", 16, 16, 0, 0);
	//player.AddComponent<TransformComponent>(glm::vec2(400.0, 300.0), glm::vec2(1.0, 1.0), 0.0);

	//Entity enemy1 = this->registry->CreateEntity();
	//enemy1.AddComponent<CircleColliderComponent>(8, 16, 16);
	//enemy1.AddComponent<RigidBodyComponent>(glm::vec2(-25, 0));
	//enemy1.AddComponent<SpriteComponent>("crushingCyclops", 16, 16, 16, 0);
	//enemy1.AddComponent<TransformComponent>(glm::vec2(600.0, 100.0), glm::vec2(2.0, 2.0), 0.0);
	//enemy1.AddComponent<AnimationComponent>(4, 4, true);
}

void Game::ProcessInput()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				isRunning = false;
				break;
			}
			controllerManager->KeyDown(sdlEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			controllerManager->KeyUp(sdlEvent.key.keysym.sym);
			break;
		default:
			break;
		}
	}
}

void Game::Update()
{
	int timeToWait = MILISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
	if (0 < timeToWait && timeToWait <= MILISECS_PER_FRAME) {
		SDL_Delay(timeToWait);
	}
	double deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
	millisecsPreviousFrame = SDL_GetTicks();
	eventManager->Reset();
	registry->GetSystem<DamageSystem>().SubscribeToCollisionEvent(eventManager);
	registry->Update();
	registry->GetSystem<ScriptSystem>().Update(lua);
	registry->GetSystem<MovementSystem>().Update(deltaTime);
	registry->GetSystem<CollisionSystem>().Update(eventManager);
	registry->GetSystem<AnimationSystem>().Update();
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 31, 31, 31, 255);
	SDL_RenderClear(renderer);
	registry->GetSystem<RenderSystem>().Update(renderer, assetManager);
	SDL_RenderPresent(renderer);
}

void Game::Run()
{
	this->Setup();
	while (this->isRunning) {
		this->ProcessInput();
		this->Update();
		this->Render();
	}
}

void Game::Destroy()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	TTF_Quit();
	SDL_Quit();
}

Game::~Game()
{
	std::cout << "GAME se ejecuta destructor" << std::endl;
	this->window = nullptr;
	this->renderer = nullptr;
	this->registry.reset();
	this->eventManager.reset();
	this->assetManager.reset();
	this->controllerManager.reset();
}
