#include "Game.hpp"

#include <iostream>

Game::Game() 
{
	this->window = nullptr;
	this->renderer = nullptr;
	this->windowHeight = 600;
	this->windowWidth = 800;
	this->isRunning = true;

	/////////////////////////////////////////////////////////////////////////////////////////

	// Para animaciones

	this->mPreviousFrame = 0;
	this->velocidad = glm::vec2();

	/////////////////////////////////////////////////////////////////////////////////////////

	// Para mostrar imágenes

	this->imgTexture = nullptr;
	this->imgPos = glm::vec2();
	this->imgWidth = 0;
	this->imgHeight = 0;
	this->imgAngle = 0.0;
	this->srcRect = { 0, 0, 0, 0 };

	/////////////////////////////////////////////////////////////////////////////////////////

	// Para mostrar texto
	
	this->font = nullptr;
	this->fontSize = 0;
	this->fontColor = { 0, 0, 0 };
	this->msg = "";
	this->msgPos = glm::vec2();
	this->msgWidth = 0;
	this->msgHeight = 0;
	this->msgAngle = 0.0;
	this->msgTexture = nullptr;

	/////////////////////////////////////////////////////////////////////////////////////////
}

Game::~Game()
{
	std::cout << "Se ejecuta destructor" << std::endl;

}

void Game::init()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error inicializando SDL!" << std::endl;
		return;
	}

	if (TTF_Init() != 0) {
		std::cerr << "Error inicializando TTF!" << std::endl;
		return;
	}

	if ((this->window = SDL_CreateWindow(
		"Tarea 01: Intro a SDL",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		this->windowWidth,
		this->windowHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	)) == NULL ) 
	{
		std::cerr << "Error creando ventana!" << std::endl;
		return;
	}

	if ((this->renderer = SDL_CreateRenderer(window, -1, 0)) == NULL) {
		std::cerr << "Error creando renderer!" << std::endl;
		return;
	}

	/////////////////////////////////////////////////////////////////////////////////////////

	// Inicializar datos para animaciones
	this->velocidad.x = 50; // 50 pxs por seg


	/////////////////////////////////////////////////////////////////////////////////////////

	// Inicializar datos de la imagen

	this->imgWidth = 32;
	this->imgHeight = 32;
	this->imgPos.x = (this->windowWidth / 2) - (this->imgWidth / 2);
	this->imgPos.y = (this->windowHeight / 2) - (this->imgHeight / 2);
	SDL_Surface* imgSurface = IMG_Load("./assets/images/pito.png");
	this->imgTexture = SDL_CreateTextureFromSurface(this->renderer, imgSurface);
	SDL_FreeSurface(imgSurface);
	this->srcRect.x = 0;
	this->srcRect.y = 0;
	this->srcRect.w = this->imgWidth;
	this->srcRect.h = this->imgHeight;

	/////////////////////////////////////////////////////////////////////////////////////////

	// Inicializar datos del texto

	this->fontSize = 20;
	this->font = TTF_OpenFont("./assets/fonts/press_start_2p.ttf", this->fontSize);
	this->msg = "Engine00";
	this->fontColor.r = 255;
	SDL_Surface* msgSurface = TTF_RenderText_Solid(this->font, this->msg.c_str(), this->fontColor );
	this->msgTexture = SDL_CreateTextureFromSurface(this->renderer, msgSurface);
	this->msgWidth = msgSurface->w;
	this->msgHeight = msgSurface->h;
	this->msgPos.x = (this->windowWidth / 2) - (this->msgWidth / 2);
	this->msgPos.y = 20;
	SDL_FreeSurface(msgSurface);

	/////////////////////////////////////////////////////////////////////////////////////////

}

void Game::run()
{
	while (this->isRunning) {
		this->processInput();
		this->update();
		this->render();
	}
}

void Game::destroy()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

void Game::processInput()
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

void Game::update()
{
	/////////////////////////////////////////////////////////////////////////////////////////

	// Calcular el tiempo de espera

	// SDL_GetTicks retorna el tiempo desde que se inicializó SDL
	int timeToWait = MS_PER_FPS - (SDL_GetTicks() - this->mPreviousFrame);
	if (timeToWait > 0 && timeToWait <= MS_PER_FPS) {
		SDL_Delay(timeToWait);
	}

	double deltaTime = (SDL_GetTicks() - this->mPreviousFrame) / 1000.0;

	this->mPreviousFrame = SDL_GetTicks();

	this->imgPos.x += this->velocidad.x * deltaTime;
	this->imgPos.y += this->velocidad.y * deltaTime;
}

void Game::render()
{
	if (SDL_SetRenderDrawColor(this->renderer, 30, 30, 30, 255) != 0) {
		std::cerr << "Error en SDL_SetRenderDrawColor!" << std::endl;
		return;
	}
	if (SDL_RenderClear(this->renderer) != 0) {
		std::cerr << "Error en SDL_RenderClear!" << std::endl;
		return;
	}

	/////////////////////////////////////////////////////////////////////////////////////////

	// Dibujar imagen

	SDL_Rect dstRect = {
		this->imgPos.x,
		this->imgPos.y,
		this->imgWidth,
		this->imgHeight
	};

	if ((SDL_RenderCopyEx(
		this->renderer,
		this->imgTexture,
		&this->srcRect,
		&dstRect,
		this->imgAngle,
		NULL,
		SDL_FLIP_NONE
	))!= 0) {
		std::cerr << "Error en SDL_RenderCopyEx img!" << std::endl;
		return;
	}

	/////////////////////////////////////////////////////////////////////////////////////

	// Dibujar texto 

	SDL_Rect msgDstRect = {
	this->msgPos.x,
	this->msgPos.y,
	this->msgWidth,
	this->msgHeight
	};

	if ((SDL_RenderCopyEx(
		this->renderer,
		this->msgTexture,
		NULL,
		&msgDstRect,
		this->msgAngle,
		NULL,
		SDL_FLIP_NONE
	)) != 0) {
		std::cerr << "Error en SDL_RenderCopyEx text!" << std::endl;
		return;
	}

	/////////////////////////////////////////////////////////////////////////////////////

	SDL_RenderPresent(this->renderer);
}
