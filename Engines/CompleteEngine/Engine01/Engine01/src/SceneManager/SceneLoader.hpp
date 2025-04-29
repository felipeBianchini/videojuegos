#ifndef SCENELOADER_HPP
#define SCENELOADER_HPP

#include <string>
#include <memory>
#include <sol/sol.hpp>
#include <SDL.h>

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
#include "../Components/HealthComponent.hpp"
#include "../Components/ScoreComponent.hpp"
#include "../Components/EntityTypeComponent.hpp"

#include "../ECS/ECS.hpp"

class SceneLoader {
private:
	void LoadSprites(SDL_Renderer* renderer, const sol::table& sprites, std::unique_ptr<AssetManager>& assetManager);
	void LoadKeys(const sol::table& keys, std::unique_ptr<ControllerManager>& controllerManager);
	void LoadEntities(sol::state& lua, const sol::table& entities, std::unique_ptr<Registry>& registry);
	void LoadFonts(const sol::table& fonts, std::unique_ptr<AssetManager>& assetManager);
	void LoadButtons(const sol::table& buttons, std::unique_ptr<ControllerManager>& controllerManager);
	void LoadBackgrounds(SDL_Renderer* renderer, const sol::table& backgrounds, std::unique_ptr<AssetManager>& assetManager);
public:
	SceneLoader();
	~SceneLoader();
	void LoadScene(const std::string& scenePath,
		sol::state& lua, SDL_Renderer* renderer,
		std::unique_ptr<AssetManager>& assetManager,
		std::unique_ptr<ControllerManager>& controllerManager,
		std::unique_ptr<Registry>& registry
	);
};

#endif // !SCENELOADER_HPP