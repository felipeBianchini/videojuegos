#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <SDL.h>
#include <SDL_image.h>

#include <map>
#include <string>

class AssetManager {
 public:
	 AssetManager();
	 ~AssetManager();
	 void ClearAssets();
	 void AddTexture(SDL_Renderer* renderer, const std::string& textureId, const std::string& filePath);
	 SDL_Texture* GetTexture(const std::string& textureId);
 private:
	 std::map<std::string, SDL_Texture*> textures;

};

#endif // !ASSET_MANAGER_HPP
