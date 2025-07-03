#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include <string>
#include <memory>
#include <sol/sol.hpp>
#include <tinyxml/tinyxml2.h>
#include <SDL2/SDL.h>

#include "../AssetManager/AssetManager.hpp"
#include "../ControllerManager/ControllerManager.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/ClickableComponent.hpp"
#include "../Components/CameraFollowComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../AnimationManager/AnimationManager.hpp"
#include "../ECS/ECS.hpp"

class SceneLoader {
private:
	void LoadSprites(SDL_Renderer* renderer, const sol::table& sprites, std::unique_ptr<AssetManager>& assetManager);
	void LoadKeys(const sol::table& keys, std::unique_ptr<ControllerManager>& controllerManager);
	void LoadEntities(sol::state& lua, const sol::table& entities, std::unique_ptr<Registry>& registry);
	void LoadFonts(const sol::table& fonts, std::unique_ptr<AssetManager>& assetManager);
	void LoadButtons(const sol::table& buttons, std::unique_ptr<ControllerManager>& controllerManager);
	void LoadMap(const sol::table map, std::unique_ptr<Registry>& registry);
	void LoadLayer(std::unique_ptr<Registry>& registry, tinyxml2::XMLElement* layer, int tileWidth, int tileHeigth, int mapWidth, int columns, const std::string& tileSet);
	void LoadColliders(std::unique_ptr<Registry>& registry, tinyxml2::XMLElement* objectGroup);
	void LoadAnimations(const sol::table& animations, std::unique_ptr<AnimationManager>& animationManager);
    /**
     * @brief Loads sound effect assets into the AssetManager.
     *
     * Processes the sound effects table from the Lua configuration and loads the corresponding sound
     * effects into the AssetManager.
     *
     * @param soundEffects The Lua table containing sound effect configuration data.
     * @param assetManager A unique pointer to the AssetManager for storing loaded sound effects.
     */
    void LoadSoundEffects(const sol::table& soundEffects, std::unique_ptr<AssetManager>& assetManager);

    /**
     * @brief Loads background music assets into the AssetManager.
     *
     * Processes the background music table from the Lua configuration and loads the corresponding
     * background music into the AssetManager.
     *
     * @param backgroundMusic The Lua table containing background music configuration data.
     * @param assetManager A unique pointer to the AssetManager for storing loaded background music.
     */
    void LoadBackgroundMusic(const sol::table& backgroundMusic, std::unique_ptr<AssetManager>& assetManager);
    void LoadBackgroundImage(const sol::table& backgroundImages, std::unique_ptr<Registry>& registry);
public:
	SceneLoader();
	~SceneLoader();
	void LoadScene(const std::string& scenePath,
		sol::state& lua, SDL_Renderer* renderer,
		std::unique_ptr<AnimationManager>& animationManager,
		std::unique_ptr<AssetManager>& assetManager,
		std::unique_ptr<ControllerManager>& controllerManager,
		std::unique_ptr<Registry>& registry
	);
};

#endif // !SCENELOADER_HPP