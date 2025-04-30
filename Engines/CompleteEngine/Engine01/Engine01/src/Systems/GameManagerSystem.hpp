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
	}

	void SetGameTimer(double gameTimer, std::string nextScene) {
		this->gameTimer = gameTimer;
		if (this->nextScene == "main_menu" || this->nextScene.empty()) {
			this->nextScene = nextScene;
		}
	}

	void Update(double dt, std::string sceneType, sol::state& lua) {
		if (sceneType == "notGame") {
			return;
		}

		playerHealth = player.GetComponent<HealthComponent>().health;
		playerScore = player.GetComponent<ScoreComponent>().score;

		gameTimer -= dt;

		UpdatePlayerScore(std::to_string(playerScore));
		CheckPlayerHealth(sceneType, lua);
	}

	void UpdatePlayerScore(std::string playerScore) {
		score.GetComponent<TextComponent>().text = ("Score: " + playerScore);
	}

	void CheckPlayerHealth(std::string sceneType, sol::state& lua) {
		if (playerHealth <= 0) {
			this->gameOver = true;
			lua["defeat"]();
		}

		if (gameTimer <= 0.0f && playerHealth > 0) {
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

	void SetPlayerScore(const Entity& entity) {
		score = entity;
	}

	void SetPlayer(const Entity& entity) {
		player = entity;
	}

private:
	double gameTimer;
	bool gameOver;
	std::string nextScene;
	int playerHealth;
	int playerScore;
	Entity player;
	Entity score;
};

#endif // !GAMEMANAGERSYSTEM_HPP
