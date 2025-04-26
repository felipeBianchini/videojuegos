#include "AssetManager.hpp"

#include <iostream>

AssetManager::AssetManager()
{
	this->backgroundTexture = nullptr;
	std::cout << "[AssetManager] Se ejecuta constructor" << std::endl;
}

AssetManager::~AssetManager()
{
	std::cout << "[AssetManager] Se ejecuta destructor" << std::endl;
}

void AssetManager::ClearAssets()
{
	if (backgroundTexture) {
		SDL_DestroyTexture(backgroundTexture);
	}
	for (auto texture : textures) {
		SDL_DestroyTexture(texture.second);
	}
	textures.clear();
	for (auto font : fonts) {
		TTF_CloseFont(font.second);
	}
	fonts.clear();
}

void AssetManager::AddTexture(SDL_Renderer* renderer, const std::string& textureId, const std::string& filePath)
{
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	textures.emplace(textureId, texture);
}

SDL_Texture* AssetManager::GetTexture(const std::string& textureId)
{
	return textures[textureId];
}

void AssetManager::AddFont(const std::string& fontId, const std::string& filePath, int fontSize)
{
	TTF_Font* font = TTF_OpenFont(filePath.c_str(), fontSize);
	if (font == NULL) {
		std::string error = TTF_GetError();
		std::cerr << "[ASSETMANAGER] " << error << std::endl;
		return;
	}
	fonts.emplace(fontId, font);
}

TTF_Font* AssetManager::GetFont(const std::string& fontId)
{
	return fonts[fontId];
}

void AssetManager::SetBackground(SDL_Renderer* renderer, const std::string& backgroundId, const std::string& filePath)
{
	SDL_Surface* surface = IMG_Load(filePath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	textures.emplace(backgroundId, texture);
}

SDL_Texture* AssetManager::GetBackground(const std::string& backgroundId)
{
	return textures[backgroundId];
}
