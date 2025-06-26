#include <iostream>

#include "Game.hpp"

#include "../Events/ClickEvent.hpp"

#include "../Systems/RenderSystem.hpp"
#include "../Systems/MovementSystem.hpp"
#include "../Systems/CircleCollisionSystem.hpp"
#include "../Systems/DamageSystem.hpp"
#include "../Systems/AnimationSystem.hpp"
#include "../Systems/ScriptSystem.hpp"
#include "../Systems/RenderTextSystem.hpp"
#include "../Systems/UISystem.hpp"
#include "../Systems/CameraMovementSystem.hpp"
#include "../Systems/BoxCollisionSystem.hpp"
#include "../Systems/RenderBoxColliderSystem.hpp"
#include "../Systems/PhysicsSystem.hpp"
#include "../Systems/OverlapSystem.hpp"

Game::Game()
{
	std::cout << "GAME se ejecuta constructor" << std::endl;
	this->window = nullptr;
	this->renderer = nullptr;
	this->isRunning = true;
	this->window_width = 1280;
	this->window_height = 720;
	this->registry = std::make_unique<Registry>();
	assetManager = std::make_unique<AssetManager>();
	eventManager = std::make_unique<EventManager>();
	controllerManager = std::make_unique<ControllerManager>();
	sceneManager = std::make_unique<SceneManager>();
	animationManager = std::make_unique<AnimationManager>();
	camera.x = 0;
	camera.y = 0;
	camera.w = this->window_width;
	camera.h = this->window_height;
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

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		std::cerr << "Error inicializando SDL_mixer: " << Mix_GetError() << std::endl;
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
	registry->AddSystem<CircleCollisionSystem>();
	registry->AddSystem<DamageSystem>();
	registry->AddSystem<AnimationSystem>();
	registry->AddSystem<RenderTextSystem>();
	registry->AddSystem<ScriptSystem>();
	registry->AddSystem<UISystem>();
	registry->AddSystem<CameraMovementSystem>();
	registry->AddSystem<BoxCollisionSystem>();
	registry->AddSystem<RenderBoxColliderSystem>();
	registry->AddSystem<PhysicsSystem>();
	registry->AddSystem<OverlapSystem>();

	sceneManager->LoadSceneFromScript("./assets/scripts/scenes.lua", lua);

	lua.open_libraries(sol::lib::base, sol::lib::math);

	registry->GetSystem<ScriptSystem>().CreateLuaBinding(lua);
}

void Game::ProcessInput()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
		case SDL_QUIT:
			sceneManager->StopScene();
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				sceneManager->StopScene();
				isRunning = false;
				break;
			}
			if (sdlEvent.key.keysym.sym == SDLK_i) {
				isDebugMode = !isDebugMode;
				break;
			}
			controllerManager->KeyDown(sdlEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			controllerManager->KeyUp(sdlEvent.key.keysym.sym);
			break;
		case SDL_MOUSEMOTION:
			int x, y;
			SDL_GetMouseState(&x, &y);
			controllerManager->SetMousePosition(x, y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			controllerManager->SetMousePosition(sdlEvent.button.x, sdlEvent.button.y);
			controllerManager->MouseButtonDown(static_cast<int>(sdlEvent.button.button));
			eventManager->EmitEvent<ClickEvent>(static_cast<int>(sdlEvent.button.button), sdlEvent.button.x, sdlEvent.button.y);
			break;
		case SDL_MOUSEBUTTONUP:
			controllerManager->SetMousePosition(sdlEvent.button.x, sdlEvent.button.y);
			controllerManager->MouseButtonUp(static_cast<int>(sdlEvent.button.button));
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
	registry->GetSystem<UISystem>().SubscribeToClickEvent(eventManager);
	registry->GetSystem<OverlapSystem>().SubscribeToCollisionEvent(eventManager);
	//registry->GetSystem<DamageSystem>().SubscribeToCollisionEvent(eventManager);
	registry->Update();
	registry->GetSystem<ScriptSystem>().Update(lua, deltaTime);
	registry->GetSystem<PhysicsSystem>().Update();
	registry->GetSystem<MovementSystem>().Update(deltaTime);
	registry->GetSystem<BoxCollisionSystem>().Update(lua, eventManager);
	registry->GetSystem<CircleCollisionSystem>().Update(eventManager);
	registry->GetSystem<AnimationSystem>().Update();
	registry->GetSystem<CameraMovementSystem>().Update(camera);
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 31, 31, 31, 255);
	SDL_RenderClear(renderer);
	registry->GetSystem<RenderSystem>().Update(renderer, assetManager, camera);
	registry->GetSystem<RenderTextSystem>().Update(renderer, assetManager);
	if (isDebugMode) {
		registry->GetSystem<RenderBoxColliderSystem>().Update(renderer, camera);
	}
	SDL_RenderPresent(renderer);
}

void Game::RunScene()
{
	sceneManager->LoadScene();
	while (sceneManager->IsSceneRunning()) {
		ProcessInput();
		Update();
		Render();
	}
	assetManager->ClearAssets();
	registry->ClearAllEntities();
}

void Game::Run()
{
	this->Setup();
	while (this->isRunning) {
		sceneManager->StartScene();
		RunScene();
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
	this->sceneManager.reset();
	this->animationManager.reset();
}
