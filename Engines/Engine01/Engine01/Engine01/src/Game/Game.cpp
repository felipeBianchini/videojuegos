#include <iostream>

#include "Game.hpp"
#include "../Components/TransformComponent.hpp"

Game::Game()
{
	this->window = nullptr;
	this->renderer = nullptr;
	this->isRunning = true;
	this->window_width = 800;
	this->window_height = 600;
	this->registry = std::make_unique<Registry>();
	std::cout << "GAME se ejecuta constructor" << std::endl;
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

void Game::Run()
{
	this->Setup();
	while (this->isRunning) {
		this->ProcessInput();
		this->Update();
		this->Render();
	}
}

void Game::Setup()
{
	Entity e = this->registry->CreateEntity();
	e.AddComponent<TransformComponent>(glm::vec2(100.0, 100.0), glm::vec2(1.0, 1.0), 0.0);
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
}

void Game::Render()
{
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
}
