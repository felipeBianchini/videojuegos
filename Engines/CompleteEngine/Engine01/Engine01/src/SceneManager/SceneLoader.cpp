#include "SceneLoader.hpp"
#include "../Systems/GameManagerSystem.hpp"

#include <iostream>
#include <glm/glm.hpp>

SceneLoader::SceneLoader()
{
	std::cout << "[SceneLoader] se ejecuta constructor" << std::endl;
}

SceneLoader::~SceneLoader()
{
	std::cout << "[SceneLoader] se ejecuta destructor" << std::endl;
}

void SceneLoader::LoadSprites(SDL_Renderer* renderer, const sol::table& sprites, std::unique_ptr<AssetManager>& assetManager)
{
	int index = 1;
	while (true) {
		sol::optional<sol::table> hasSprite = sprites[index];
		if (hasSprite == sol::nullopt) {
			break;
		}
		sol::table sprite = sprites[index];
		std::string assetId = sprite["assetId"];
		std::string filePath = sprite["filePath"];
		assetManager->AddTexture(renderer, assetId, filePath);
		index++;
	}
}

void SceneLoader::LoadBackgrounds(SDL_Renderer* renderer, const sol::table& backgrounds, std::unique_ptr<AssetManager>& assetManager)
{
	int index = 1;
	while (true) {
		sol::optional<sol::table> hasBackground = backgrounds[index];
		if (hasBackground == sol::nullopt) {
			break;
		}
		sol::table background = backgrounds[index];
		std::string backgroundId = background["backgroundId"];
		std::string filePath = background["filePath"];
		assetManager->SetBackground(renderer, backgroundId, filePath);
		index++;
	}
}

void SceneLoader::LoadKeys(const sol::table& keys, std::unique_ptr<ControllerManager>& controllerManager)
{
	int index = 1;
	while (true) {
		sol::optional<sol::table> hasKey = keys[index];
		if (hasKey == sol::nullopt) {
			break;
		}
		sol::table key = keys[index];
		std::string name = key["name"];
		int keyCode = key["key"];
		controllerManager->AddActionKey(name, keyCode);
		index++;
	}
}

void SceneLoader::LoadEntities(sol::state& lua, const sol::table& entities, std::unique_ptr<Registry>& registry)
{
	int index = 1;
	while (true) {
		sol::optional<sol::table> hasEntity = entities[index];
		if (hasEntity == sol::nullopt) {
			break;
		}
		sol::table entity = entities[index];
		Entity newEntity = registry->CreateEntity();
		sol::optional<sol::table> hasComponents = entity["components"];
		if (hasComponents != sol::nullopt) {
			sol::table components = entity["components"];
			// AnimationComponent
			// CircleColliderComponent
			sol::optional<sol::table> hasCircleCollider = components["circle_collider"];
			if (hasCircleCollider != sol::nullopt) {
				newEntity.AddComponent<CircleColliderComponent>(
					components["circle_collider"]["radius"],
					components["circle_collider"]["width"],
					components["circle_collider"]["heigth"]
				);
			}
			// ClickableComponent
			sol::optional<sol::table> hasClickable = components["clickable"];
			if (hasClickable != sol::nullopt) {
				newEntity.AddComponent<ClickableComponent>();
			}
			// RigidBodyComponent
			sol::optional<sol::table> hasRigidBody = components["rigid_body"];
			if (hasRigidBody != sol::nullopt) {
				newEntity.AddComponent<RigidBodyComponent>(
					glm::vec2(
						components["rigid_body"]["velocity"]["x"],
						components["rigid_body"]["velocity"]["y"]
					)
				);
			}
			// ScriptComponent
			sol::optional<sol::table> hasScript = components["script"];
			if (hasScript != sol::nullopt) {
				lua["on_click"] = sol::nil;
				lua["update"] = sol::nil;
				lua["updateBullets"] = sol::nil;
				lua["createEnemy1"] = sol::nil;
				lua["updateEnemy1Position"] = sol::nil;
				std::string path = components["script"]["path"];
				lua.script_file(path);
				sol::optional<sol::function> hasUpdate = lua["update"];
				sol::function update = sol::nil;
				if (hasUpdate != sol::nullopt) {
					update = lua["update"];
				}
				sol::optional<sol::function> hasOnClick = lua["on_click"];
				sol::function onClick = sol::nil;
				if (hasOnClick != sol::nullopt) {
					onClick = lua["on_click"];
				}
				sol::optional<sol::function> hasUpdateBullets = lua["updateBullets"];
				sol::function updateBullets = sol::nil;
				if (hasUpdateBullets != sol::nullopt) {
					updateBullets = lua["updateBullets"];
				}
				sol::optional<sol::function> hasCreateEnemy1 = lua["createEnemy1"];
				sol::function createEnemy1 = sol::nil;
				if (hasCreateEnemy1 != sol::nullopt) {
					createEnemy1 = lua["createEnemy1"];
				}
				sol::optional<sol::function> hasUpdateEnemy1Position = lua["updateEnemy1Position"];
				sol::function updateEnemy1Position = sol::nil;
				if (hasUpdateEnemy1Position != sol::nullopt) {
					updateEnemy1Position = lua["updateEnemy1Position"];
				}
				sol::optional<sol::function> hasCreateEnemy2 = lua["createEnemy2"];
				sol::function createEnemy2 = sol::nil;
				if (hasCreateEnemy2 != sol::nullopt) {
					createEnemy2 = lua["createEnemy2"];
				}
				newEntity.AddComponent<ScriptComponent>(update, onClick, updateBullets, updateEnemy1Position, createEnemy1, createEnemy2);
			}
			// SpriteComponent
			sol::optional<sol::table> hasSprite = components["sprite"];
			if (hasSprite != sol::nullopt) {
				newEntity.AddComponent<SpriteComponent>(
					components["sprite"]["assetId"],
					components["sprite"]["width"],
					components["sprite"]["heigth"],
					components["sprite"]["src_rect"]["x"],
					components["sprite"]["src_rect"]["y"]
				);
			}
			// TextComponent
			sol::optional<sol::table> hasText = components["text"];
			if (hasText != sol::nullopt) {
				newEntity.AddComponent<TextComponent>(
					components["text"]["text"],
					components["text"]["fontId"],
					components["text"]["r"],
					components["text"]["g"],
					components["text"]["b"],
					components["text"]["a"]
				);
			}
			// TransformComponent
			sol::optional<sol::table> hasTransform = components["transform"];
			if (hasTransform != sol::nullopt) {
				newEntity.AddComponent<TransformComponent>(
					glm::vec2(
						components["transform"]["position"]["x"],
						components["transform"]["position"]["y"]
					),
					glm::vec2(
						components["transform"]["scale"]["x"],
						components["transform"]["scale"]["y"]
					),
					components["transform"]["rotation"]
				);
			}
			// HealthComponent
			sol::optional<sol::table> hasHealth = components["health"];
			if (hasHealth) {
				sol::optional<int> health = (*hasHealth)["health"];
				if (health) {
					newEntity.AddComponent<HealthComponent>(*health);
				}
			}
			// ScoreComponent
			sol::optional<sol::table> hasScore = components["score"];
			if (hasScore != sol::nullopt) {
				sol::optional<int> score = (*hasScore)["score"];
				if (score) {
					newEntity.AddComponent<ScoreComponent>(*score);
				}
			}
			// EntityTypeComponent
			sol::optional<sol::table> hasType = components["type"];
			if (hasType != sol::nullopt) {
				sol::optional<int> type = (*hasType)["type"];
				if (type) {
					newEntity.AddComponent<EntityTypeComponent>(*type);
				}
			}
		}
		if (newEntity.HasComponent<EntityTypeComponent>() && newEntity.GetComponent<EntityTypeComponent>().entityType == 1) {
			registry->GetSystem<GameManagerSystem>().SetPlayer(newEntity);
		}
		else if (newEntity.HasComponent<EntityTypeComponent>() && newEntity.GetComponent<EntityTypeComponent>().entityType == 0) {
			registry->GetSystem<GameManagerSystem>().SetPlayerScore(newEntity);
		}
		else if (newEntity.HasComponent<EntityTypeComponent>() && newEntity.GetComponent<EntityTypeComponent>().entityType == -1) {
			registry->GetSystem<GameManagerSystem>().SetPlayerHealth(newEntity);
		}
		else if (newEntity.HasComponent<EntityTypeComponent>() && newEntity.GetComponent<EntityTypeComponent>().entityType == -2) {
			registry->GetSystem<GameManagerSystem>().SetGameTimer(newEntity);
		}
		index++;
	}
}

void SceneLoader::LoadFonts(const sol::table& fonts, std::unique_ptr<AssetManager>& assetManager)
{
	int index = 1;
	while (true) {
		sol::optional<sol::table> hasFont = fonts[index];
		if (hasFont == sol::nullopt) {
			break;
		}
		sol::table font = fonts[index];
		std::string fontId = font["fontId"];
		std::string filePath = font["filePath"];
		int fontSize = font["fontSize"];
		assetManager->AddFont(fontId, filePath, fontSize);
		index++;
	}
}

void SceneLoader::LoadButtons(const sol::table& buttons, std::unique_ptr<ControllerManager>& controllerManager)
{
	int index = 1;
	while (true) {
		sol::optional<sol::table> hasButton = buttons[index];
		if (hasButton == sol::nullopt) {
			break;
		}
		sol::table button = buttons[index];
		std::string name = button["name"];
		int buttonCode = button["button"];
		controllerManager->AddMouseButton(name, buttonCode);
		index++;
	}
}

void SceneLoader::LoadScene(const std::string& scenePath, sol::state& lua, SDL_Renderer* renderer, std::unique_ptr<AssetManager>& assetManager, std::unique_ptr<ControllerManager>& controllerManager, std::unique_ptr<Registry>& registry)
{
	sol::load_result script_result = lua.load_file(scenePath);
	if (!script_result.valid()) {
		sol::error err = script_result;
		std::string errMessage = err.what();
		std::cerr << "[SCENELOADER] " << errMessage << std::endl;
		return;
	}
	lua.script_file(scenePath);
	sol::table scene = lua["scene"];
	sol::table sprites = scene["sprites"];
	LoadSprites(renderer, sprites, assetManager);
	sol::table backgrounds = scene["backgrounds"];
	LoadBackgrounds(renderer, backgrounds, assetManager);
	sol::table fonts = scene["fonts"];
	LoadFonts(fonts, assetManager);
	sol::table buttons = scene["buttons"];
	LoadButtons(buttons, controllerManager);
	sol::table keys = scene["keys"];
	LoadKeys(keys, controllerManager);
	sol::table entities = scene["entities"];
	LoadEntities(lua, entities, registry);
}
