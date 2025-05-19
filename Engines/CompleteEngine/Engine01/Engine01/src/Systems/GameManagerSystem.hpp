#ifndef GAMEMANAGERSYSTEM_HPP
#define GAMEMANAGERSYSTEM_HPP

#include "../Components/HealthComponent.hpp"
#include "../Components/ScoreComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../ECS/ECS.hpp"

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
        UpdatePlayerHealth(std::to_string(playerHealth));
        UpdateTimer(std::to_string(static_cast<int>(gameTimer)));
        CheckPlayerHealth(sceneType, lua);
    }

    void UpdatePlayerHealth(const std::string& playerHealthStr) {
        if (!health.HasComponent<TextComponent>()) {
            return;
        }
        auto& text = health.GetComponent<TextComponent>();
        text.text = "Health: " + playerHealthStr;
    }

    void UpdatePlayerScore(const std::string& playerScoreStr) {
        if (!score.HasComponent<TextComponent>()) {
            return;
        }
        auto& text = score.GetComponent<TextComponent>();
        text.text = "Score: " + playerScoreStr;
    }

    void UpdateTimer(const std::string& gameTimer) {
        if (!gameTime.HasComponent<TextComponent>()) {
            return;
        }
        auto& text = gameTime.GetComponent<TextComponent>();
        text.text = "Time: " + gameTimer;
    }

    void CheckPlayerHealth(const std::string& sceneType, sol::state& lua) {
        if (playerHealth <= 0) {
            this->gameOver = true;
            if (lua["defeat"].valid()) {
                lua["defeat"]();
            }
        }

        if (gameTimer <= 0.0f && playerHealth > 0) {
            if (lua["victory"].valid()) {
                lua["victory"]();
            }
        }
    }
    // TODO: REVISAR CUANDO SE PIERDE
    void GoToNextScene(sol::state& lua) {
        std::cout << this->nextScene << std::endl;

        if (!this->gameOver) {
            if (this->nextScene == "level_01") {
                this->nextScene = "level_02";
            }
            else if (this->nextScene == "level_02") {
                this->nextScene = "level_03";
            }
            else if (this->nextScene == "level_03") {
                this->nextScene = "level_01";
            }
        }

        std::cout << this->nextScene << std::endl;

        if (lua["go_to_scene"].valid()) {
            lua["go_to_scene"](nextScene);
        }
    }

    void SetGameTimer(const Entity& entity) {
        gameTime = entity;
    }

    void SetPlayerHealth(const Entity& entity) {
        health = entity;
    }

    void SetPlayerScore(const Entity& entity) {
        score = entity;
    }

    void SetPlayer(const Entity& entity) {
        player = entity;
    }

    Entity GetPlayer() {
        return this->player;
    }

private:
    double gameTimer;
    bool gameOver;
    std::string nextScene;
    int playerHealth;
    int playerScore;
    Entity player;
    Entity score;
    Entity health;
    Entity gameTime;
};

#endif // GAMEMANAGERSYSTEM_HPP
