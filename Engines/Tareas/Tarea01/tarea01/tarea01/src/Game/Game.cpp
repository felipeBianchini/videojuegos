#include "Game.hpp"

#include <iostream>

Game::Game()
{
	this->window = nullptr;
	this->renderer = nullptr;
	this->windw = nullptr;
	this->fnt = nullptr;
	this->isRunning = true;
	this->keepMoving = true;
	this->mPreviousFrame = 0;
	this->font = nullptr;
	this->fontColor = { 0, 0, 0 };
	this->msg = "";
	this->msgPos = glm::vec2();
	this->msgWidth = 0;
	this->msgHeight = 0;
	this->msgAngle = 0.0;
	this->msgTexture = nullptr;
}

Game::Game(Window* window, Font* font, std::vector<Entity*> entities) : Game()
{
	this->windw = window;
	this->fnt = font;
	this->entities = entities;
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
		this->windw->width,
		this->windw->height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	)) == NULL)
	{
		std::cerr << "Error creando ventana!" << std::endl;
		return;
	}

	if ((this->renderer = SDL_CreateRenderer(window, -1, 0)) == NULL) {
		std::cerr << "Error creando renderer!" << std::endl;
		return;
	}

	for (auto entity : entities)
	{
		SDL_Surface* imgSurface = IMG_Load(entity->getFilename().c_str());
		SDL_Texture* imgTexture = SDL_CreateTextureFromSurface(this->renderer, imgSurface);
		entity->setTexture(imgTexture);
		SDL_FreeSurface(imgSurface);
		SDL_Rect rect = { 0, 0, 0, 0 };
		rect.x = 0;
		rect.y = 0;
		rect.w = entity->getWidth();
		rect.h = entity->getHeight();
		entity->setSrcRect(rect);
	}

	this->font = TTF_OpenFont(this->fnt->filename.c_str(), this->fnt->fontSize);
	this->msg = "Tarea01";
	this->fontColor.r = this->fnt->r;
	this->fontColor.g = this->fnt->g;
	this->fontColor.b = this->fnt->b;
	SDL_Surface* msgSurface = TTF_RenderText_Solid(this->font, this->msg.c_str(), this->fontColor);
	this->msgTexture = SDL_CreateTextureFromSurface(this->renderer, msgSurface);
	this->msgWidth = msgSurface->w;
	this->msgHeight = msgSurface->h;
	this->msgPos.x = (this->windw->width / 2) - (this->msgWidth / 2);
	this->msgPos.y = 20;

	SDL_FreeSurface(msgSurface);
}

void Game::run()
{
	while (this->isRunning) {
		this->processInput();
		this->update();
		this->render();
	}
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
			else if (sdlEvent.key.keysym.sym == SDLK_p) {
				this->keepMoving = !this->keepMoving;
			}
			break;
		default:
			break;
		}
	}
}

void Game::update()
{
	int timeToWait = MS_PER_FPS - (SDL_GetTicks() - this->mPreviousFrame);
	if (timeToWait > 0 && timeToWait <= MS_PER_FPS) {
		SDL_Delay(timeToWait);
	}

	double deltaTime = (SDL_GetTicks() - this->mPreviousFrame) / 1000.0;

	this->mPreviousFrame = SDL_GetTicks();
	double newPosX = 0.0;
	double newPosY = 0.0;
	double newVelX = 0.0;
	double newVelY = 0.0;
	if (this->keepMoving) {
		for (auto entity : entities)
		{
			newPosX = entity->getImgPosX() + (entity->getVelocidadX() * deltaTime);
			entity->setImgPosX(newPosX);
			newPosY = entity->getImgPosY() + (entity->getVelocidadY() * deltaTime);
			entity->setImgPosY(newPosY);
			if (entity->getImgPosX() <= 0 || entity->getImgPosX() + entity->getWidth() >= this->windw->width) {
				newVelX = entity->getVelocidadX() * -1;
				entity->setVelocidadX(newVelX);

			}
			if (entity->getImgPosY() <= 0 || entity->getImgPosY() + entity->getHeight() >= this->windw->height) {
				newVelY = entity->getVelocidadY() * -1;
				entity->setVelocidadY(newVelY);
			}
		}
	}
}


void Game::render()
{
	if (SDL_SetRenderDrawColor(this->renderer, this->windw->r, this->windw->g, this->windw->b, 255) != 0) {
		std::cerr << "Error en SDL_SetRenderDrawColor!" << std::endl;
		return;
	}
	if (SDL_RenderClear(this->renderer) != 0) {
		std::cerr << "Error en SDL_RenderClear!" << std::endl;
		return;
	}
	for (auto entity : entities)
	{
		int imgX = entity->getImgPosX();
		int imgY = entity->getImgPosY();
		int imgWidth = entity->getWidth();
		int imgHeight = entity->getHeight();
		SDL_Rect dstRect = { imgX, imgY, imgWidth, imgHeight };
		if ((SDL_RenderCopyEx(
			this->renderer,
			entity->getTexture(),
			&entity->getSrcRect(),
			&dstRect,
			entity->getAngle(),
			NULL,
			SDL_FLIP_NONE
		)) != 0) {
			std::cerr << "Error en SDL_RenderCopyEx img!" << std::endl;
			return;
		}
		SDL_Surface* labelSurface = TTF_RenderText_Solid(this->font, entity->getLabel().c_str(), this->fontColor);
		SDL_Texture* labelTexture = SDL_CreateTextureFromSurface(this->renderer, labelSurface);

		int labelWidth = labelSurface->w;
		int labelHeight = labelSurface->h;
		SDL_FreeSurface(labelSurface);
		SDL_Rect labelDstRect = {
		imgX + (imgWidth / 2) - (labelWidth / 2),
		imgY + (imgHeight / 2) - (labelHeight / 2),
		labelWidth,
		labelHeight
		};
		if ((SDL_RenderCopyEx(
			this->renderer,
			labelTexture,
			NULL,
			&labelDstRect,
			0,
			NULL,
			SDL_FLIP_NONE
		)) != 0) {
			std::cerr << "Error en SDL_RenderCopyEx label!" << std::endl;
		}

		SDL_DestroyTexture(labelTexture);
	}

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
	SDL_RenderPresent(this->renderer);
}



void Game::destroy()
{
	if (this->renderer) {
		SDL_DestroyRenderer(this->renderer);
		this->renderer = nullptr;
	}
	if (this->window) {
		SDL_DestroyWindow(this->window);
		this->window = nullptr;
	}
	if (msgTexture) {
		SDL_DestroyTexture(msgTexture);
		msgTexture = nullptr;
	}
	if (font) {
		TTF_CloseFont(font);
		font = nullptr;
	}
	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
}

Game::~Game()
{
	for (auto entity : entities) {
		delete entity;
	}
	entities.clear();
	delete windw;
	delete fnt;
}