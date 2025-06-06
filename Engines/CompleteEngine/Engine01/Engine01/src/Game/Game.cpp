#include <iostream>

#include "Game.hpp"

#include "../Events/ClickEvent.hpp"

#include "../Systems/RenderSystem.hpp"
#include "../Systems/MovementSystem.hpp"
#include "../Systems/CollisionSystem.hpp"
#include "../Systems/DamageSystem.hpp"
#include "../Systems/AnimationSystem.hpp"
#include "../Systems/ScriptSystem.hpp"
#include "../Systems/RenderTextSystem.hpp"
#include "../Systems/UISystem.hpp"
#include "../Systems/GameManagerSystem.hpp"
#include "../Systems/IsEntityInsideTheScreenSystem.hpp"

Game::Game()
{
	std::cout << "GAME se ejecuta constructor" << std::endl;
	this->window = nullptr;
	this->renderer = nullptr;
	this->isRunning = true;
	this->keepRunning = true;
	this->window_width = 1200;
	this->window_height = 800;
	this->registry = std::make_unique<Registry>();
	assetManager = std::make_unique<AssetManager>();
	eventManager = std::make_unique<EventManager>();
	controllerManager = std::make_unique<ControllerManager>();
	sceneManager = std::make_unique<SceneManager>();
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
	registry->AddSystem<CollisionSystem>();
	registry->AddSystem<DamageSystem>();
	registry->AddSystem<AnimationSystem>();
	registry->AddSystem<RenderTextSystem>();
	registry->AddSystem<ScriptSystem>();
	registry->AddSystem<UISystem>();
	registry->AddSystem<GameManagerSystem>();
	registry->AddSystem<IsEntityInsideTheScreenSystem>();

	sceneManager->LoadSceneFromScript("./assets/scripts/scenes.lua", lua);

	lua.open_libraries(sol::lib::base, sol::lib::math);

	lua.script_file("./assets/scripts/endGameConditions.lua");
	lua.script_file("./assets/scripts/go_to_next_scene.lua");

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
			else if (sdlEvent.key.keysym.sym == SDLK_p) {
				this->keepRunning = !keepRunning;
			}
			controllerManager->KeyDown(sdlEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			controllerManager->KeyUp(sdlEvent.key.keysym.sym);
			break;
		case SDL_MOUSEMOTION:
			int x, y;
			SDL_GetMouseState(&x, &y);
			controllerManager->SetMousePosition(x,y);
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
	registry->GetSystem<DamageSystem>().SubscribeToCollisionEvent(eventManager);
	registry->Update();
	registry->GetSystem<GameManagerSystem>().Update(deltaTime, sceneManager->GetCurrentSceneType(), lua);
	registry->GetSystem<ScriptSystem>().Update(lua, deltaTime, window_height, window_width);
	registry->GetSystem<MovementSystem>().Update(deltaTime, window_height, window_width, registry->GetSystem<GameManagerSystem>().GetPlayer());
	registry->GetSystem<IsEntityInsideTheScreenSystem>().Update(window_width, window_height);
	registry->GetSystem<CollisionSystem>().Update(eventManager);
	registry->GetSystem<AnimationSystem>().Update();
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 31, 31, 31, 255);
	SDL_RenderClear(renderer);
	registry->GetSystem<RenderSystem>().Update(renderer, assetManager);
	registry->GetSystem<RenderTextSystem>().Update(renderer, assetManager);
	SDL_RenderPresent(renderer);
}

void Game::RunScene()
{
	sceneManager->LoadScene();
	registry->GetSystem<GameManagerSystem>().SetGameTimer(sceneManager->GetCurrentSceneTimer());
	while (sceneManager->IsSceneRunning()) {
		ProcessInput();
		if (this->keepRunning) {
			Update();
		}
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
	Mix_CloseAudio();
	Mix_Quit();
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
}
