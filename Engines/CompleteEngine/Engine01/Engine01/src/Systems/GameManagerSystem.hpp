#ifndef GAMEMANAGERSYSTEM_HPP
#define GAMEMANAGERSYSTEM_HPP

#include "../Binding/LuaBinding.hpp"
#include "../ECS/ECS.hpp"

#define GAMETIMEDURATION = 120

class GameManagerSystem : public System {
public:
	GameManagerSystem() {
		this->gameTimer = 0.0f;
		this->gameOver = false;
		this->nextScene = "";
	}

	void SetGameTimer(double gameTimer, std::string nextScene) {
		this->gameTimer = gameTimer;
		if (this->nextScene == "main_menu" || this->nextScene.empty()) {
			this->nextScene = nextScene;
		}
	}

	void Update(double dt, std::string sceneType, sol::state& lua) {
		int playerLife = 10;

		if (gameOver || sceneType == "notGame") {
			return;
		}

		gameTimer -= dt;

		if (playerLife <= 0) {
			lua["defeat"]();
		}

		if (gameTimer <= 0.0f && playerLife > 0) {
			lua["victory"]();
		}
	}

	void GoToNextScene(sol::state& lua) {
		if (this->nextScene == "level_01") {
			this->nextScene = "level_02";
		}
		else if (this->nextScene == "level_02") {
			this->nextScene = "level_03";
		}
		else if (this->nextScene == "level_03") {
			this->nextScene = "level_01";
		}
		std::cout << nextScene << std::endl;
		lua["go_to_scene"](nextScene);
	}
private:
	double gameTimer;
	bool gameOver;
	std::string nextScene;
};

#endif // !GAMEMANAGERSYSTEM_HPP
