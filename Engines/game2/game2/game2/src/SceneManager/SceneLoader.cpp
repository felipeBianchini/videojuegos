#include "SceneLoader.hpp"

#include "../Game/Game.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <sstream>

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
			sol::optional<sol::table> hasAnimation = components["animation"];
			if (hasAnimation != sol::nullopt) {
				newEntity.AddComponent<AnimationComponent>(
					components["animation"]["num_frames"],
					components["animation"]["speed_rate"],
					components["animation"]["is_loop"]
				);
			}
			// BoxColliderComponent
			sol::optional<sol::table> hasBoxCollider = components["box_collider"];
			if (hasBoxCollider != sol::nullopt) {
				newEntity.AddComponent<BoxColliderComponent>(
					components["box_collider"]["width"],
					components["box_collider"]["heigth"],
					glm::vec2(
						components["box_collider"]["offset"]["x"],
						components["box_collider"]["offset"]["y"]
					)
				);
			}
			// CameraFollowComponent
			sol::optional<sol::table> hasCameraFollow = components["camera_follow"];
			if (hasCameraFollow != sol::nullopt) {
				newEntity.AddComponent<CameraFollowComponent>();
			}
			// TagComponent
			sol::optional<sol::table> hasTag = components["tag"];
			if (hasTag != sol::nullopt) {
				std::string tag = components["tag"]["tag"];
				newEntity.AddComponent<TagComponent>(tag);
			}
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
					components["rigid_body"]["is_dynamic"],
					components["rigid_body"]["is_solid"],
					components["rigid_body"]["mass"]
				);
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
			// ScriptComponent
			sol::optional<sol::table> hasScript = components["script"];
			if (hasScript != sol::nullopt) {
				lua["on_click"] = sol::nil;
				lua["update"] = sol::nil;
				lua["on_collision"] = sol::nil;
				lua["on_awake"] = sol::nil;
				std::string path = components["script"]["path"];
				lua.script_file(path);
				sol::optional<sol::function> hasOnAwake = lua["on_awake"];
				if (hasOnAwake != sol::nullopt) {
					lua["this"] = newEntity;
					sol::function OnAwake = lua["on_awake"];
					OnAwake();
				}
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
				sol::optional<sol::function> hasOnCollision = lua["on_collision"];
				sol::function onCollision = sol::nil;
				if (hasOnCollision != sol::nullopt) {
					onCollision = lua["on_collision"];
				}
				newEntity.AddComponent<ScriptComponent>(onCollision, update, onClick);
			}
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

void SceneLoader::LoadMap(const sol::table map, std::unique_ptr<Registry>& registry)
{
	sol::optional<int> hasWidth = map["width"];
	if (hasWidth != sol::nullopt) {
		Game::GetInstance().mapWidth = map["width"];
	}
	sol::optional<int> hasHeigth = map["heigth"];
	if (hasHeigth != sol::nullopt) {
		Game::GetInstance().mapHeigth = map["heigth"];
	}
	sol::optional<std::string> hasPath = map["map_path"];
	if (hasPath != sol::nullopt) {

		std::string mapPath = map["map_path"];
		tinyxml2::XMLDocument xmlmap;
		xmlmap.LoadFile(mapPath.c_str());
		tinyxml2::XMLElement* xmlRoot = xmlmap.RootElement();

		int tWidth, tHeigth, mWidth, mHeigth;
		xmlRoot->QueryIntAttribute("tilewidth", &tWidth);
		xmlRoot->QueryIntAttribute("tileheight", &tHeigth);
		xmlRoot->QueryIntAttribute("width", &mWidth);
		xmlRoot->QueryIntAttribute("height", &mHeigth);
		Game::GetInstance().mapWidth = tWidth * mWidth;
		Game::GetInstance().mapHeigth = tHeigth * mHeigth;

		std::string tilePath = map["tile_path"];
		std::string tileName = map["tile_name"];
		tinyxml2::XMLDocument xmltileset;
		xmltileset.LoadFile(tilePath.c_str());
		tinyxml2::XMLElement* xmlTilesetRoot = xmltileset.RootElement();
		int columns;
		xmlTilesetRoot->QueryIntAttribute("columns", &columns);

		tinyxml2::XMLElement* xmlLayer = xmlRoot->FirstChildElement("layer");
		while (xmlLayer != nullptr) {
			LoadLayer(registry, xmlLayer, tWidth, tHeigth, mWidth, columns, tileName);
			xmlLayer = xmlLayer->NextSiblingElement("layer");
		}
		tinyxml2::XMLElement* xmlObjectGroup = xmlRoot->FirstChildElement("objectgroup");
		while (xmlObjectGroup != nullptr) {
			const char* objectGroupName;
			std::string ogName;
			xmlObjectGroup->QueryStringAttribute("name", &objectGroupName);
			ogName = objectGroupName;
			if (ogName.compare("colliders") == 0) {
				LoadColliders(registry, xmlObjectGroup);
			}
			xmlObjectGroup = xmlObjectGroup->NextSiblingElement("objectgroup");
		}
	}
}

void SceneLoader::LoadLayer(std::unique_ptr<Registry>& registry, tinyxml2::XMLElement* layer, int tileWidth, int tileHeigth, int mapWidth, int columns, const std::string& tileSet)
{
	tinyxml2::XMLElement* xmlData = layer->FirstChildElement("data");
	const char* data = xmlData->GetText();
	std::stringstream tmpNumber;
	int pos = 0;
	int tileNumber = 0;
	while (true) {
		if (data[pos] == '\0') {
			break;
		}
		if (isdigit(data[pos])) {
			tmpNumber << data[pos];
		}
		else if (!isdigit(data[pos]) && tmpNumber.str().length() != 0) {
			int tileId = std::stoi(tmpNumber.str());
			if (tileId > 0) {
				Entity tile = registry->CreateEntity();
				tile.AddComponent<TransformComponent>(
					glm::vec2(
						(tileNumber % mapWidth) * tileWidth,
						(tileNumber / mapWidth) * tileHeigth
					)
				);
				tile.AddComponent<SpriteComponent>(
					tileSet,
					tileWidth,
					tileHeigth,
					((tileId - 1) % columns) * tileWidth,
					((tileId - 1) / columns) * tileHeigth
				);
			}
			tileNumber++;
			tmpNumber.str("");
		}
		pos++;
	}
}

void SceneLoader::LoadColliders(std::unique_ptr<Registry>& registry, tinyxml2::XMLElement* objectGroup)
{
	tinyxml2::XMLElement* object = objectGroup->FirstChildElement("object");
	while (object != nullptr) {
		const char* name;
		std::string tag;
		int x, y, w, h;
		object->QueryStringAttribute("name", &name);
		tag = name;
		object->QueryIntAttribute("x", &x);
		object->QueryIntAttribute("y", &y);
		object->QueryIntAttribute("width", &w);
		object->QueryIntAttribute("height", &h);
		Entity collider = registry->CreateEntity();
		collider.AddComponent<TagComponent>(tag);
		collider.AddComponent<TransformComponent>(glm::vec2(x, y));
		collider.AddComponent<BoxColliderComponent>(w, h);
		collider.AddComponent<RigidBodyComponent>(false, true, 9999999999.0f);
		object = object->NextSiblingElement("object");
	}
}

void SceneLoader::LoadAnimations(const sol::table& animations, std::unique_ptr<AnimationManager>& animationManager)
{
	int index = 1;
	while (true) {
		sol::optional<sol::table> hasAnimation = animations[index];
		if (hasAnimation == sol::nullopt) {
			break;
		}
		sol::table animation = animations[index];
		std::string animationId = animation["animation_id"];
		std::string textureId = animation["texture_id"];
		int width = animation["w"];
		int height = animation["h"];
		int numFrames = animation["num_frames"];
		int speedRate = animation["speed_rate"];
		bool isLoop = animation["is_loop"];
		animationManager->AddAnimation(animationId, textureId, width, height, numFrames, speedRate, isLoop);
		index++;
	}
}

void SceneLoader::LoadScene(const std::string& scenePath, sol::state& lua, SDL_Renderer* renderer, std::unique_ptr<AnimationManager>& animationManager, std::unique_ptr<AssetManager>& assetManager, std::unique_ptr<ControllerManager>& controllerManager, std::unique_ptr<Registry>& registry)
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
	sol::table animations = scene["animations"];
	LoadAnimations(animations, animationManager);
	sol::table fonts = scene["fonts"];
	LoadFonts(fonts, assetManager);
	sol::table buttons = scene["buttons"];
	LoadButtons(buttons, controllerManager);
	sol::table keys = scene["keys"];
	LoadKeys(keys, controllerManager);
	sol::table maps = scene["maps"];
	LoadMap(maps, registry);
	sol::table entities = scene["entities"];
	LoadEntities(lua, entities, registry);
}
