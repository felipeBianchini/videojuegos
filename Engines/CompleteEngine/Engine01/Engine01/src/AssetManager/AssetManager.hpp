#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <map>
#include <string>

class AssetManager {
 public:
	 AssetManager();
	 ~AssetManager();
	 void ClearAssets();
	 void AddTexture(SDL_Renderer* renderer, const std::string& textureId, const std::string& filePath);
	 SDL_Texture* GetTexture(const std::string& textureId);
	 void AddFont(const std::string& fontId, const std::string& filePath, int fontSize);
	 TTF_Font* GetFont(const std::string& fontId);
	 void SetBackground(SDL_Renderer* renderer, const std::string& backgroundId, const std::string& filePath );
	 SDL_Texture* GetBackground(const std::string& backgroundId);
private:
	 std::map<std::string, SDL_Texture*> textures;
	 std::map<std::string, TTF_Font*> fonts;
	 SDL_Texture* backgroundTexture = nullptr;
};

#endif // !ASSET_MANAGER_HPP
