#ifndef GAMEMANAGERSYSTEM_HPP
#define GAMEMANAGERSYSTEM_HPP

#include "../Components/HealthComponent.hpp"
#include "../ECS/ECS.hpp"

#define GAMETIMEDURATION = 120

class GameManagerSystem : public System {
public:
	GameManagerSystem() {
		this->playerHealth = 0;
		this->gameTimer = 0.0f;
		this->gameOver = false;
		this->nextScene = "";
		this->hasPlayer = false;
		this->player = nullptr;
	}

	void SetGameTimer(double gameTimer, std::string nextScene) {
		this->gameTimer = gameTimer;
		if (this->nextScene == "main_menu" || this->nextScene.empty()) {
			this->nextScene = nextScene;
		}
	}

	void Update(double dt, std::string sceneType, sol::state& lua) {
		if (sceneType == "notGame" || !hasPlayer) {
			return;
		}

		if (player->HasComponent<HealthComponent>()) {
			playerHealth = player->GetComponent<HealthComponent>().health;
		}

		gameTimer -= dt;

		if (playerHealth <= 0) {
			std::cout << playerHealth << std::endl;
			this->gameOver = true;
			lua["defeat"]();
		}

		if (gameTimer <= 0.0f && playerHealth > 0) {
			std::cout << playerHealth << std::endl;

			lua["victory"]();
		}
	}

	void GoToNextScene(sol::state& lua) {
		if (this->nextScene == "level_01") {
			if (!this->gameOver) {
				this->nextScene = "level_02";
			}
		}
		else if (this->nextScene == "level_02") {
			if (!this->gameOver) {
				this->nextScene = "level_03";
			}
		}
		else if (this->nextScene == "level_03") {
			if (!this->gameOver) {
				this->nextScene = "level_01";
			}
		}
		lua["go_to_scene"](nextScene);
	}

	void SetPlayer(Entity* playerEntity) {
		if (!playerEntity) {
			std::cout << "[GameManager] ERROR: playerEntity es nullptr!" << std::endl;
			return;
		}
		player = playerEntity;
		playerHealth = player->GetComponent<HealthComponent>().health;
		hasPlayer = true;
	}



private:
	double gameTimer;
	bool gameOver;
	std::string nextScene;
	int playerHealth;
	Entity* player;
	bool hasPlayer;
};

#endif // !GAMEMANAGERSYSTEM_HPP
