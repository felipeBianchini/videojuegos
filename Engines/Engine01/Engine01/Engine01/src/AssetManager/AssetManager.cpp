#include "AssetManager.hpp"

#include <iostream>

AssetManager::AssetManager()
{
	std::cout << "[AssetManager] Se ejecuta constructor" << std::endl;
}

AssetManager::~AssetManager()
{
	std::cout << "[AssetManager] Se ejecuta destructor" << std::endl;
}

void AssetManager::ClearAssets()
{
	for (auto texture : textures) {
		SDL_DestroyTexture(texture.second);
	}
	textures.clear();
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
