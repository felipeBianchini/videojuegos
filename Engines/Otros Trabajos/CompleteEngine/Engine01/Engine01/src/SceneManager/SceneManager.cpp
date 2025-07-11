#include "SceneManager.hpp"
#include "../Game/Game.hpp"

#include <iostream>

SceneManager::SceneManager()
{
	std::cout << "[SCENEMANAGER] Se ejecuta constructor" << std::endl;
	sceneLoader = std::make_unique<SceneLoader>();
}

SceneManager::~SceneManager()
{
	std::cout << "[SCENEMANAGER] Se ejecuta destructor" << std::endl;
	sceneLoader.reset();
}

void SceneManager::LoadSceneFromScript(const std::string& path, sol::state& lua)
{
	lua.script_file(path);
	sol::table scenes = lua["scenes"];
	int index = 1;
	while (true) {
		sol::optional<sol::table> hasScene = scenes[index];
		if (hasScene == sol::nullopt) {
			break;
		}
		sol::table scene = scenes[index];
		this->scenes.emplace(scene["name"], scene["path"]);
		if (index == 1) {
			nextScene = scene["name"];
		}
		index++;
	}
}

void SceneManager::LoadScene()
{
	Game& game = Game::GetInstance();
	std::string scenePath = scenes[nextScene];
	sceneLoader->LoadScene(scenePath, game.lua, game.renderer, game.assetManager, game.controllerManager, game.registry);

}

std::string SceneManager::GetNextScene() const
{
	return nextScene;
}

void SceneManager::SetNextScene(const std::string& nextScene)
{
	this->nextScene = nextScene;
}

bool SceneManager::IsSceneRunning() const
{
	return isSceneRunning;
}

void SceneManager::StartScene()
{
	isSceneRunning = true;
}

void SceneManager::StopScene()
{
	isSceneRunning = false;
}
