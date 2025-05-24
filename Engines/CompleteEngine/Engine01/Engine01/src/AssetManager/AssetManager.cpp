#include "AssetManager.hpp"

#include <iostream>

AssetManager::AssetManager()
{
	this->backgroundTexture = nullptr;
	this->backgroundMusic = nullptr;
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
		backgroundMusic = nullptr;
	}
	if (backgroundMusic) {
		Mix_FreeMusic(backgroundMusic);
		backgroundMusic = nullptr;
	}
	for (auto texture : textures) {
		SDL_DestroyTexture(texture.second);
	}
	textures.clear();
	for (auto font : fonts) {
		TTF_CloseFont(font.second);
	}
	fonts.clear();
	for (auto soundEffect : soundEffects) {
		Mix_FreeChunk(soundEffect.second);
	}
	soundEffects.clear();
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

void AssetManager::AddSoundEffect(const std::string& soundEffectId, const std::string& filePath)
{
	Mix_Chunk* chunk = Mix_LoadWAV(filePath.c_str());
	if (!chunk) {
		std::string error = Mix_GetError();
		std::cerr << "[ASSETMANAGER] " << error << std::endl;
		return;
	}
	soundEffects.emplace(soundEffectId, chunk);
}

Mix_Chunk* AssetManager::GetSoundEffect(const std::string& soundEffectId)
{
	return soundEffects[soundEffectId];
}

void AssetManager::SetBackgroundMusic(const std::string& backgroundMusicId, const std::string& filePath)
{
	backgroundMusic = Mix_LoadMUS(filePath.c_str());
	if (!backgroundMusic) {
		std::string error = Mix_GetError();
		std::cerr << "[ASSETMANAGER] " << error << std::endl;
		return;
	}
}

Mix_Music* AssetManager::GetBackgroundMusic(const std::string& backgroundMusicId)
{
	return backgroundMusic;
}
