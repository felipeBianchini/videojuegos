#include <iostream>

#include "Game.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Systems/RenderSystem.hpp"
#include "../Systems/MovementSystem.hpp"
#include "../Systems/CollisionSystem.hpp"
#include "../Systems/DamageSystem.hpp"
#include "../Systems/AnimationSystem.hpp"

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
		"Game Engine 01: Patron ECS",
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
	assetManager->AddTexture(renderer, "blindedGrimlock", "./assets/images/BlindedGrimlock.png");
	assetManager->AddTexture(renderer, "crushingCyclop", "./assets/images/CrushingCyclops.png");
	Entity enemy1 = this->registry->CreateEntity();
	enemy1.AddComponent<CircleColliderComponent>(8, 16, 16);
	enemy1.AddComponent<RigidBodyComponent>(glm::vec2(50, 0));
	enemy1.AddComponent<SpriteComponent>("blindedGrimlock", 16, 16, 0, 0);
	enemy1.AddComponent<TransformComponent>(glm::vec2(200.0, 100.0), glm::vec2(2.0, 2.0), 0.0);
	enemy1.AddComponent<AnimationComponent>(4
		, 10, true);

	Entity enemy2 = this->registry->CreateEntity();
	enemy2.AddComponent<CircleColliderComponent>(8, 16, 16);
	enemy2.AddComponent<RigidBodyComponent>(glm::vec2(-50, 0));
	enemy2.AddComponent<SpriteComponent>("crushingCyclop", 16, 16, 0, 0);
	enemy2.AddComponent<TransformComponent>(glm::vec2(600.0, 100.0), glm::vec2(2.0, 2.0), 0.0);
	enemy2.AddComponent<AnimationComponent>(4, 10, true);
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
			}
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
	registry.reset();
	this->window = nullptr;
	this->renderer = nullptr;
	this->assetManager.reset();
}
