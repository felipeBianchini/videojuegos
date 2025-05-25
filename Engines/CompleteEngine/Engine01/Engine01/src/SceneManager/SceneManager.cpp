#include "SceneManager.hpp"
#include "../Game/Game.hpp"

#include <iostream>

SceneManager::SceneManager()
{
	std::cout << "[SCENEMANAGER] Se ejecuta constructor" << std::endl;
	sceneLoader = std::make_unique<SceneLoader>();
	this->currentSceneTimer = 0.0;
	this->currentSceneType = "";
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
		std::string name = scene["name"];
		std::string path = scene["path"];
		std::string type = scene["type"];
		double timer = static_cast<double>(scene["time"]);
		this->scenes.emplace(name, path);
		this->sceneTypes.emplace(name, type);
		this->sceneTimers.emplace(name, timer);
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
	this->currentSceneType = sceneTypes[nextScene];
	this->currentSceneTimer = sceneTimers[nextScene];
	sceneLoader->LoadScene(scenePath, game.lua, game.renderer, game.assetManager, game.controllerManager, game.registry);
	Mix_Music* music = Game::GetInstance().assetManager->GetBackgroundMusic("background_music");
	if (music != nullptr) {
		Mix_PlayMusic(music, -1);
	}
	else {
		std::cerr << " ERROR [SceneManager::StartScene]: Music" << std::endl;
	}
}

std::string SceneManager::GetNextScene() const
{
	return this->nextScene;
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

std::string SceneManager::GetCurrentSceneType()
{
	return this->currentSceneType;
}

double SceneManager::GetCurrentSceneTimer()
{
	return this->currentSceneTimer;
}
