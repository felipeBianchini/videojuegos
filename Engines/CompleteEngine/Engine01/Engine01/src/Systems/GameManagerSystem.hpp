#ifndef GAMEMANAGERSYSTEM_HPP
#define GAMEMANAGERSYSTEM_HPP

#include "../Components/HealthComponent.hpp"
#include "../Components/ScoreComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Game/Game.hpp"
#include "../ECS/ECS.hpp"

#include <thread>
#include <chrono>

/**
 * @class GameManagerSystem
 * @brief A system for managing game state and UI updates within an Entity-Component-System (ECS) architecture.
 *
 * This system oversees game state, including player health, score, timer, and boss health. It updates UI elements,
 * handles game progression, triggers sound effects, and manages transitions between scenes based on game events
 * such as player death, boss defeat, or timer expiration.
 */
class GameManagerSystem : public System {
public:
    /**
     * @brief Constructor for the GameManagerSystem.
     *
     * Initializes the system with default values for game timer, game over state, and other variables.
     */
    GameManagerSystem() {
        this->playerHealth = 0;
        this->gameTimer = 0.0f;
        this->gameOver = false;
        this->nextScene = "";
    }
    /**
     * @brief Sets the game timer duration.
     *
     * @param gameTimer The duration of the game timer in seconds.
     */
    void SetGameTimer(double gameTimer) {
        this->gameTimer = gameTimer;
    }
    /**
     * @brief Updates the game state and UI elements.
     *
     * Updates player health, score, timer, and boss health, and checks conditions for game over, victory,
     * or scene transitions. Executes Lua scripts for specific events if available.
     *
     * @param dt Delta time since the last update, used for timer updates.
     * @param sceneType The type of the current scene (e.g., "notGame" to skip updates).
     * @param lua The Lua state for executing script callbacks.
     */
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
    /**
     * @brief Updates the player's health display.
     *
     * Updates the text of the health entity's TextComponent to reflect the current player health.
     *
     * @param playerHealthStr The player's health as a string.
     */
    void UpdatePlayerHealth(const std::string& playerHealthStr) {
        if (!health.HasComponent<TextComponent>()) {
            return;
        }
        auto& text = health.GetComponent<TextComponent>();
        text.text = "Health: " + playerHealthStr;
    }
    /**
     * @brief Updates the player's score display.
     *
     * Updates the text of the score entity's TextComponent to reflect the current player score.
     *
     * @param playerScoreStr The player's score as a string.
     */
    void UpdatePlayerScore(const std::string& playerScoreStr) {
        if (!score.HasComponent<TextComponent>()) {
            return;
        }
        auto& text = score.GetComponent<TextComponent>();
        text.text = "Score: " + playerScoreStr;
    }
    /**
     * @brief Updates the game timer display.
     *
     * Updates the text of the game time entity's TextComponent to reflect the current game timer.
     *
     * @param gameTimer The game timer value as a string.
     */
    void UpdateTimer(const std::string& gameTimer) {
        if (!gameTime.HasComponent<TextComponent>()) {
            return;
        }
        auto& text = gameTime.GetComponent<TextComponent>();
        text.text = "Time: " + gameTimer;
    }
    /**
     * @brief Updates the game timer display.
     *
     * Updates the text of the game time entity's TextComponent to reflect the current game timer.
     *
     * @param gameTimer The game timer value as a string.
     */
    void UpdateBossHealth() {
        if (!bossHealthEnt.HasComponent<TextComponent>()) {
            return;
        }
        std::string bossHealth = std::to_string(boss.GetComponent<HealthComponent>().health);
        auto& text = bossHealthEnt.GetComponent<TextComponent>();
        text.text = "Boss Health: " + bossHealth;
    }
    /**
     * @brief Checks if the player has died and triggers game over.
     *
     * If the player's health is zero or less, sets the next scene and triggers the Lua defeat script.
     *
     * @param lua The Lua state for executing the defeat script.
     */
    void CheckPlayerHealth(sol::state& lua) {
        if (playerHealth <= 0) {
            SetNextScene(Game::GetInstance().sceneManager->GetNextScene());
            this->gameOver = true;
            if (lua["defeat"].valid()) {
                lua["defeat"]();
            }
        }
    }
    /**
     * @brief Checks if the game timer has expired and triggers victory.
     *
     * If the timer reaches zero and the player is alive with no boss present, sets the next scene
     * and triggers the Lua victory script.
     *
     * @param lua The Lua state for executing the victory script.
     */
    void CheckClock(sol::state& lua) {
        if (gameTimer <= 0.0f && playerHealth > 0 && !boss.HasComponent<HealthComponent>()) {
            SetNextScene(Game::GetInstance().sceneManager->GetNextScene());
            if (lua["victory"].valid()) {
                lua["victory"]();
            }
        }
    }
    /**
     * @brief Checks if the boss has died and triggers death sequence.
     *
     * If the boss's health is zero or less and the player is alive, marks the boss for deletion,
     * activates death assets, and starts the boss death timer.
     *
     * @param lua The Lua state for potential script execution.
     */
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
    /**
     * @brief Activates visual and audio effects for boss death.
     *
     * Plays a sound effect and creates an explosion entity with appropriate components for animation.
     */
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
    /**
     * @brief Plays a sound effect using the asset manager.
     *
     * Retrieves and plays a sound effect with the specified ID at a set volume.
     *
     * @param soundEffectId The ID of the sound effect to play.
     */
    void PlaySoundEffect(std::string soundEffectId) {
        Mix_Chunk* soundEffect = Game::GetInstance().assetManager->GetSoundEffect(soundEffectId);
        if (soundEffect) {
            Mix_VolumeChunk(soundEffect, 75);
            Mix_PlayChannel(-1, soundEffect, 0);
        }
    }
    /**
     * @brief Transitions to the next scene based on the current scene.
     *
     * Updates the nextScene variable based on a predefined progression and triggers the Lua go_to_scene script.
     *
     * @param lua The Lua state for executing the go_to_scene script.
     */
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
    /**
     * @brief Sets the ID of the next scene to transition to.
     *
     * @param nextScene The ID of the next scene.
     */
    void SetNextScene(std::string nextScene) {
        this->nextScene = nextScene;
    }
    /**
     * @brief Sets the entity representing the game timer UI.
     *
     * @param entity The entity with the TextComponent for the game timer.
     */
    void SetGameTimer(const Entity& entity) {
        gameTime = entity;
    }
    /**
     * @brief Sets the entity representing the player health UI.
     *
     * @param entity The entity with the TextComponent for the player health.
     */
    void SetPlayerHealth(const Entity& entity) {
        health = entity;
    }
    /**
     * @brief Sets the entity representing the player score UI.
     *
     * @param entity The entity with the TextComponent for the player score.
     */
    void SetPlayerScore(const Entity& entity) {
        score = entity;
    }
    /**
     * @brief Sets the entity representing the boss health UI.
     *
     * @param entity The entity with the TextComponent for the boss health.
     */
    void SetBossHealth(const Entity& entity) {
        bossHealthEnt = entity;
    }
    /**
     * @brief Sets the player entity.
     *
     * @param entity The entity representing the player.
     */
    void SetPlayer(const Entity& entity) {
        player = entity;
    }
    /**
     * @brief Gets the player entity.
     *
     * @return The player entity.
     */
    Entity GetPlayer() {
        return this->player;
    }
    /**
     * @brief Sets the boss entity.
     *
     * @param entity The entity representing the boss.
     */
    void SetBoss(const Entity& entity) {
        this->boss = entity;
    }
    /**
     * @brief Gets the boss entity.
     *
     * @return The boss entity.
     */
    Entity GetBoss() {
        return this->boss;
    }

private:
    double gameTimer;                ///< Tracks the elapsed game time in seconds.
    bool gameOver;                   ///< Indicates whether the game has ended.
    std::string nextScene;           ///< Name of the next scene to load after the current one ends.
    int playerHealth;                ///< Current health value of the player.
    int playerScore;                 ///< Current score of the player.

    Entity player;                   ///< Entity representing the player character.
    Entity score;                    ///< Entity used to display the player's score.
    Entity health;                   ///< Entity used to display the player's health.
    Entity gameTime;                 ///< Entity used to display the elapsed game time.
    Entity bossHealthEnt;            ///< Entity used to display the boss's health bar.
    Entity boss;                     ///< Entity representing the boss character.

    bool bossDying = false;          ///< Flag indicating if the boss is in its death animation/state.
    float bossDeathTimer = 0.0f;     ///< Timer used to control the boss death animation or delay.


};

#endif // GAMEMANAGERSYSTEM_HPP
