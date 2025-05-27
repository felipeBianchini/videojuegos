#ifndef GAMEMANAGERSYSTEM_HPP
#define GAMEMANAGERSYSTEM_HPP

#include "../Components/HealthComponent.hpp"
#include "../Components/ScoreComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Game/Game.hpp"
#include "../ECS/ECS.hpp"

#include <thread>
#include <chrono>

class GameManagerSystem : public System {
public:
    GameManagerSystem() {
        this->playerHealth = 0;
        this->gameTimer = 0.0f;
        this->gameOver = false;
        this->nextScene = "";
    }

    void SetGameTimer(double gameTimer) {
        this->gameTimer = gameTimer;
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
        UpdateBossHealth();
        CheckPlayerHealth(lua);
        CheckClock(lua);
        CheckBossHealth(lua);
        if (bossDying) {
            bossDeathTimer -= dt;
            if (bossDeathTimer <= 0.0f) {
                SetNextScene(Game::GetInstance().sceneManager->GetNextScene());
                bossDying = false;
                if (lua["victory"].valid()) {
                    lua["victory"]();
                }
            }
        }
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

    void UpdateBossHealth() {
        if (!bossHealthEnt.HasComponent<TextComponent>()) {
            return;
        }
        std::string bossHealth = std::to_string(boss.GetComponent<HealthComponent>().health);
        auto& text = bossHealthEnt.GetComponent<TextComponent>();
        text.text = "Boss Health: " + bossHealth;
    }

    void CheckPlayerHealth(sol::state& lua) {
        if (playerHealth <= 0) {
            SetNextScene(Game::GetInstance().sceneManager->GetNextScene());
            this->gameOver = true;
            if (lua["defeat"].valid()) {
                lua["defeat"]();
            }
        }
    }

    void CheckClock(sol::state& lua) {
        if (gameTimer <= 0.0f && playerHealth > 0 && !boss.HasComponent<HealthComponent>()) {
            SetNextScene(Game::GetInstance().sceneManager->GetNextScene());
            if (lua["victory"].valid()) {
                lua["victory"]();
            }
        }
    }

    void CheckBossHealth(sol::state& lua) {
        if (!boss.HasComponent<HealthComponent>()) {
            return;
        }
        if (boss.GetComponent<HealthComponent>().health <= 0 && playerHealth > 0) {
            boss.Kill();
            ActivateBossDeathAssets();
            bossDying = true;
            bossDeathTimer = 3.0f;
        }
    }

    void ActivateBossDeathAssets() {
        PlaySoundEffect("bossDeath");
        const int frameWidth = 152;
        const int frameHeight = 166;
        const float scale = 3.0f;
        auto& transform = boss.GetComponent<TransformComponent>();
        glm::vec2 position(
            transform.position.x - 50,
            transform.position.y - 100
        );
        Entity explosion = Game::GetInstance().registry->CreateEntity();
        explosion.AddComponent<RigidBodyComponent>(glm::vec2(0, 0));
        explosion.AddComponent<SpriteComponent>("enemydeath1", frameWidth, frameHeight, 0, 0);
        explosion.AddComponent<TransformComponent>(position, glm::vec2(scale, scale), 0.0);
        explosion.AddComponent<AnimationComponent>(11, 4);
        explosion.AddComponent<EntityTypeComponent>(12);
    }

    void PlaySoundEffect(std::string soundEffectId) {
        Mix_Chunk* soundEffect = Game::GetInstance().assetManager->GetSoundEffect(soundEffectId);
        if (soundEffect) {
            Mix_VolumeChunk(soundEffect, 75);
            Mix_PlayChannel(-1, soundEffect, 0);
        }
    }

    void GoToNextScene(sol::state& lua) {
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
        else {

        }
        if (lua["go_to_scene"].valid()) {
            lua["go_to_scene"](nextScene);
        }
    }

    void SetNextScene(std::string nextScene) {
        this->nextScene = nextScene;
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

    void SetBossHealth(const Entity& entity) {
        bossHealthEnt = entity;
    }

    void SetPlayer(const Entity& entity) {
        player = entity;
    }

    Entity GetPlayer() {
        return this->player;
    }

    void SetBoss(const Entity& entity) {
        this->boss = entity;
    }

    Entity GetBoss() {
        return this->boss;
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
    Entity bossHealthEnt;
    Entity boss;
    bool bossDying = false;
    float bossDeathTimer = 0.0f;

};

#endif // GAMEMANAGERSYSTEM_HPP
