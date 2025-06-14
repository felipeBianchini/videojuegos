#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include <map>
#include <string>

/**
 * @brief Manages game assets such as textures, fonts, sounds, and music.
 */
class AssetManager {
 public:
	 /**
	  * @brief Constructs a new AssetManager.
	  */
	 AssetManager();
	 /**
	  * @brief Destroys the AssetManager and frees all assets.
	  */
	 ~AssetManager();
	 /**
	  * @brief Clears all loaded assets from memory.
	  */
	 void ClearAssets();
	 /**
	  * @brief Loads a texture from file and stores it under a given ID.
	  * @param renderer The SDL renderer.
	  * @param textureId Unique identifier for the texture.
	  * @param filePath Path to the texture image file.
	  */
	 void AddTexture(SDL_Renderer* renderer, const std::string& textureId, const std::string& filePath);
	 /**
	  * @brief Retrieves a texture by its ID.
	  * @param textureId The ID of the texture.
	  * @return SDL_Texture* The requested texture, or nullptr if not found.
	  */
	 SDL_Texture* GetTexture(const std::string& textureId);
	 /**
	  * @brief Loads a font from file and stores it under a given ID.
	  * @param fontId Unique identifier for the font.
	  * @param filePath Path to the font file.
	  * @param fontSize Size of the font.
	  */
	 void AddFont(const std::string& fontId, const std::string& filePath, int fontSize);
	 /**
	  * @brief Retrieves a font by its ID.
	  * @param fontId The ID of the font.
	  * @return TTF_Font* The requested font, or nullptr if not found.
	  */
	 TTF_Font* GetFont(const std::string& fontId);
	 /**
	  * @brief Loads a background image from file and stores it under a given ID.
	  * @param renderer The SDL renderer.
	  * @param backgroundId Unique identifier for the background.
	  * @param filePath Path to the background image file.
	  */
	 void SetBackground(SDL_Renderer* renderer, const std::string& backgroundId, const std::string& filePath );
	 /**
	  * @brief Retrieves the current background texture.
	  * @param backgroundId The ID of the background texture.
	  * @return SDL_Texture* The background texture, or nullptr if not found.
	  */
	 SDL_Texture* GetBackground(const std::string& backgroundId);
	 /**
	  * @brief Loads a sound effect from file and stores it under a given ID.
	  * @param soundEffectId Unique identifier for the sound effect.
	  * @param filePath Path to the sound effect file.
	  */
	 void AddSoundEffect(const std::string& soundEffectId, const std::string& filePath);
	 /**
	  * @brief Retrieves a sound effect by its ID.
	  * @param soundEffectId The ID of the sound effect.
	  * @return Mix_Chunk* The requested sound effect, or nullptr if not found.
	  */
	 Mix_Chunk* GetSoundEffect(const std::string& soundEffectId);
	 /**
	  * @brief Loads background music from file and stores it under a given ID.
	  * @param backgroundMusicId Unique identifier for the background music.
	  * @param filePath Path to the music file.
	  */
	 void SetBackgroundMusic(const std::string& backgroundMusicId, const std::string& filePath);
	 /**
	  * @brief Retrieves the background music by its ID.
	  * @param backgroundMusicId The ID of the background music.
	  * @return Mix_Music* The requested music, or nullptr if not found.
	  */
	 Mix_Music* GetBackgroundMusic(const std::string& backgroundMusicId);
private:
	std::map<std::string, SDL_Texture*> textures;       ///< Map of texture IDs to SDL textures.
	std::map<std::string, TTF_Font*> fonts;             ///< Map of font IDs to TTF fonts.
	std::map<std::string, Mix_Chunk*> soundEffects;     ///< Map of sound effect IDs to sound chunks.
	Mix_Music* backgroundMusic;                         ///< Pointer to the loaded background music.
	SDL_Texture* backgroundTexture = nullptr;           ///< Pointer to the loaded background texture.
};

#endif // !ASSET_MANAGER_HPP
