#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>

#include "../Systems/GameManagerSystem.hpp"
#include "../Game/Game.hpp"
#include "../ECS/ECS.hpp"

/**
 * @brief Adds a ScriptComponent to an entity, binding a specific Lua function from a script file.
 *
 * @param entity The ECS entity to add the script component to.
 * @param scriptPath Path to the Lua script file.
 * @param luaFunctionName The name of the Lua function to bind.
 */
void AddScriptComponent(Entity entity, const std::string& scriptPath, const std::string& luaFunctionName);
/**
 * @brief Adds TransformComponent and RigidBodyComponent to enemy entities with randomized start positions and velocities.
 *
 * @param enemy The enemy entity.
 * @param windowHeight Height of the game window.
 * @param windowWidth Width of the game window.
 * @param type Type identifier of the entity to define behavior.
 */
void AddTransformAndRigidBodyComponent(Entity enemy, int windowHeigth, int windowWidth, int type);
/**
 * @brief Plays a sound effect by ID at a given volume.
 *
 * @param soundEffectId Identifier string of the sound effect.
 * @param volume Volume level for playback (0-128 in SDL_mixer).
 */
void PlaySoundEffect(std::string soundEffectId, int volume);
/**
 * @brief Checks if a player action is activated.
 *
 * @param action Name of the action to check.
 * @return true if activated, false otherwise.
 */
bool IsActionActivated(const std::string& action) {
	return Game::GetInstance().controllerManager->IsActionActivated(action);
};
/**
 * @brief Sets the velocity of an entity's rigid body.
 *
 * @param entity The entity whose velocity to set.
 * @param x Velocity in x-direction.
 * @param y Velocity in y-direction.
 */
void SetVelocity(Entity entity, float x, float y) {
	auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
	rigidBody.velocity.x = x;
	rigidBody.velocity.y = y;
};
/**
 * @brief Change the current scene to the specified one.
 *
 * @param sceneName Name of the scene to switch to.
 */
void GoToScene(const std::string& sceneName) {
	Game::GetInstance().sceneManager->StopScene();
	Game::GetInstance().sceneManager->SetNextScene(sceneName);
};
/**
 * @brief Advances the game to the next scene using the GameManagerSystem.
 */
void GoToNextScene() {
	Game::GetInstance().registry->GetSystem<GameManagerSystem>().GoToNextScene(Game::GetInstance().lua);
};
/**
 * @brief Creates a bullet entity at the player's position and adds relevant components.
 *
 * @param playerX X position of the player.
 * @param playerY Y position of the player.
 */
void BulletFactory(double playerX, double playerY) {
	Entity bullet = Game::GetInstance().registry->CreateEntity();
	bullet.AddComponent<CircleColliderComponent>(32, 32, 32);
	bullet.AddComponent<RigidBodyComponent>(glm::vec2(0, -400));
	bullet.AddComponent<SpriteComponent>("bullet", 64, 64, 0, 0);
	bullet.AddComponent<TransformComponent>(glm::vec2(playerX + 10, playerY + 10), glm::vec2(0.5, 0.5), 0.0);
	bullet.AddComponent<EntityTypeComponent>(2);
	PlaySoundEffect("player_shoot", 16);
}
/**
 * @brief Creates an enemy bullet entity at the enemy's position.
 *
 * @param enemyX X position of the enemy.
 * @param enemyY Y position of the enemy.
 */
void EnemyBulletsFactory(double enemyX, double enemyY) {
	glm::vec2 enemyPos(enemyX + 10, enemyY + 10);
	Entity enemyBullet = Game::GetInstance().registry->CreateEntity();
	enemyBullet.AddComponent<CircleColliderComponent>(25, 20, 42);
	enemyBullet.AddComponent<RigidBodyComponent>(glm::vec2(0, 400));
	enemyBullet.AddComponent<SpriteComponent>("enemy1projectile", 14, 42, 0, 0);
	enemyBullet.AddComponent<TransformComponent>(enemyPos, glm::vec2(1.0, 1.0), 0.0);
	enemyBullet.AddComponent<EntityTypeComponent>(4);
}
/**
 * @brief Enemy type 3 attacks by firing bullets in 8 directions.
 *
 * @param enemyX X position of the enemy.
 * @param enemyY Y position of the enemy.
 */
void Enemy3Attack(double enemyX, double enemyY) {
	glm::vec2 enemyPos(enemyX + 32, enemyY + 32);
	std::vector<glm::vec2> directions = {
		glm::vec2(0, -1), glm::vec2(0.707f, -0.707f), glm::vec2(1, 0), glm::vec2(0.707f, 0.707f),
		glm::vec2(0, 1), glm::vec2(-0.707f, 0.707f), glm::vec2(-1, 0), glm::vec2(-0.707f, -0.707f)
	};
	for (const auto& dir : directions) {
		float angle = glm::degrees(atan2(dir.y, dir.x)) - 45.0f;
		Entity enemyBullet = Game::GetInstance().registry->CreateEntity();
		enemyBullet.AddComponent<CircleColliderComponent>(32, 32, 32);
		enemyBullet.AddComponent<RigidBodyComponent>(dir * 300.0f);
		enemyBullet.AddComponent<SpriteComponent>("enemy3projectile", 32, 32, 0, 0);
		enemyBullet.AddComponent<TransformComponent>(enemyPos, glm::vec2(0.75, 0.75), angle);
		enemyBullet.AddComponent<EntityTypeComponent>(4);
	}
}
/**
 * @brief Factory function to create enemy 1.
 *
 * @param windowHeight Game window height.
 * @param windowWidth Game window width.
 */
void Enemy1Factory(int windowHeight, int windowWidth) {
	Entity enemy1 = Game::GetInstance().registry->CreateEntity();
	enemy1.AddComponent<CircleColliderComponent>(64, 64, 64);
	enemy1.AddComponent<SpriteComponent>("enemy1", 128, 128, 0, 0);
	enemy1.AddComponent<HealthComponent>(3);
	enemy1.AddComponent<ScoreComponent>(100);
	enemy1.AddComponent<EntityTypeComponent>(3);
	enemy1.AddComponent<IsEntityInsideTheScreenComponent>(false);
	AddScriptComponent(enemy1, "./assets/scripts/enemy1.lua", "updateEnemy1Position");
	AddTransformAndRigidBodyComponent(enemy1, windowHeight, windowWidth, enemy1.GetComponent<EntityTypeComponent>().entityType);
}
/**
 * @brief Factory function to create enemy 2.
 *
 * @param windowHeight Game window height.
 * @param windowWidth Game window width.
 */
void Enemy2Factory(int windowHeight, int windowWidth) {
	Entity enemy2 = Game::GetInstance().registry->CreateEntity();
	enemy2.AddComponent<CircleColliderComponent>(64, 64, 64);
	enemy2.AddComponent<SpriteComponent>("enemy2", 128, 128, 0, 0);
	enemy2.AddComponent<HealthComponent>(2);
	enemy2.AddComponent<ScoreComponent>(50);
	enemy2.AddComponent<EntityTypeComponent>(5);
	enemy2.AddComponent<IsEntityInsideTheScreenComponent>(false);
	AddTransformAndRigidBodyComponent(enemy2, windowHeight, windowWidth, enemy2.GetComponent<EntityTypeComponent>().entityType);
}
/**
 * @brief Factory function to create enemy 3.
 *
 * @param windowHeight Game window height.
 * @param windowWidth Game window width.
 */
void Enemy3Factory(int windowHeight, int windowWidth) {
	Entity enemy3 = Game::GetInstance().registry->CreateEntity();
	enemy3.AddComponent<CircleColliderComponent>(96, 96, 96);
	enemy3.AddComponent<SpriteComponent>("enemy3", 128, 128, 0, 0);
	enemy3.AddComponent<HealthComponent>(6);
	enemy3.AddComponent<ScoreComponent>(250);
	enemy3.AddComponent<EntityTypeComponent>(6);
	enemy3.AddComponent<IsEntityInsideTheScreenComponent>(false);
	AddScriptComponent(enemy3, "./assets/scripts/enemy3.lua", "updateEnemy3Position");
	AddTransformAndRigidBodyComponent(enemy3, windowHeight, windowWidth, enemy3.GetComponent<EntityTypeComponent>().entityType);
}
/**
 * @brief Factory function to create an extra life power-up at a random position.
 *
 * @param windowHeight Game window height.
 * @param windowWidth Game window width.
 */
void ExtraLifeFactory(int windowHeigth, int windowWidth) {
	Entity extraLife = Game::GetInstance().registry->CreateEntity();
	extraLife.AddComponent<CircleColliderComponent>(50, 50, 50);
	extraLife.AddComponent<SpriteComponent>("extraLife", 87, 87, 0, 0);
	extraLife.AddComponent<EntityTypeComponent>(10);
	int posX = rand() % (windowWidth - 50);
	int posY = rand() % (windowHeigth - 50);
	glm::vec2 pos = glm::vec2(posX, posY);
	extraLife.AddComponent<TransformComponent>(pos, glm::vec2(0.5, 0.5), 0.0);
}
/**
 * @brief Factory function to create a nuke power-up at a random position.
 *
 * @param windowHeight Game window height.
 * @param windowWidth Game window width.
 */
void NukeFactory(int windowHeigth, int windowWidth) {
	Entity nuke = Game::GetInstance().registry->CreateEntity();
	nuke.AddComponent<CircleColliderComponent>(50, 50, 50);
	nuke.AddComponent<SpriteComponent>("nuke", 87, 87, 0, 0);
	nuke.AddComponent<EntityTypeComponent>(11);
	int posX = rand() % (windowWidth - 50);
	int posY = rand() % (windowHeigth - 50);
	glm::vec2 pos = glm::vec2(posX, posY);
	nuke.AddComponent<TransformComponent>(pos, glm::vec2(0.5, 0.5), 0.0);
}
/**
 * @brief Creates a boss projectile entity.
 *
 * @param dirX X component of the projectile velocity.
 * @param dirY Y component of the projectile velocity.
 * @param posX X position to spawn the projectile.
 * @param posY Y position to spawn the projectile.
 */
void BossAttack(double dirX, double dirY, double posX, double posY) {
	glm::vec2 dir(dirX, dirY);
	glm::vec2 pos(posX + 25, posY + 25);
	Entity bossBullet = Game::GetInstance().registry->CreateEntity();
	bossBullet.AddComponent<CircleColliderComponent>(32, 32, 32);
	bossBullet.AddComponent<RigidBodyComponent>(dir);
	bossBullet.AddComponent<SpriteComponent>("bossProjectile", 32, 32, 0, 0);
	bossBullet.AddComponent<TransformComponent>(pos, glm::vec2(1.0, 1.0), 0.0);
	bossBullet.AddComponent<EntityTypeComponent>(13);
}

void AddScriptComponent(Entity entity, const std::string& scriptPath, const std::string& luaFunctionName) {
	sol::state& lua = Game::GetInstance().lua;
	lua.script_file(scriptPath);

	sol::function func = lua[luaFunctionName];
	if (!func.valid()) {
		std::cerr << "Lua function '" << luaFunctionName << "' not found in " << scriptPath << std::endl;
		return;
	}
	ScriptComponent script;
	if (luaFunctionName == "updateEnemy1Position") {
		script.updateEnemy1Position = func;
	}
	else if (luaFunctionName == "updateEnemy3Position") {
		script.updateEnemy3Position = func;
	}
	else if (luaFunctionName == "update") {
		script.update = func;
	}
	else if (luaFunctionName == "onClick") {
		script.onClick = func;
	}
	else if (luaFunctionName == "updateBullets") {
		script.updateBullets = func;
	}
	else if (luaFunctionName == "createEnemy1") {
		script.createEnemy1 = func;
	}
	else if (luaFunctionName == "createEnemy2") {
		script.createEnemy2 = func;
	}
	else if (luaFunctionName == "createEnemy3") {
		script.createEnemy3 = func;
	}
	else if (luaFunctionName == "createExtraLife") {
		script.createExtraLife = func;
	}
	else if (luaFunctionName == "bossMechanics") {
		script.bossMechanics = func;
	}
	else if (luaFunctionName == "createNuke") {
		script.createNuke = func;
	}

	entity.AddComponent<ScriptComponent>(script);
}


void AddTransformAndRigidBodyComponent(Entity enemy, int windowHeight, int windowWidth, int type) {
	glm::vec2 startPosition;
	glm::vec2 velocity;
	int edge = 0;
	if (type == 6) {
		edge = rand() % 4; // 0: izquierda, 1: derecha, 2: arriba, 3: abajo
		switch (edge) {
		case 0:
			startPosition = glm::vec2(-64, rand() % windowHeight);
			velocity = glm::vec2(100, 0);
			break;
		case 1:
			startPosition = glm::vec2(windowWidth + 64, rand() % windowHeight);
			velocity = glm::vec2(-100, 0);
			break;
		case 2:
			startPosition = glm::vec2(rand() % windowWidth, -64);
			velocity = glm::vec2(0, 100);
			break;
		case 3:
			startPosition = glm::vec2(rand() % windowWidth, windowHeight + 64);
			velocity = glm::vec2(0, -100);
			break;
		}
		enemy.AddComponent<TransformComponent>(startPosition, glm::vec2(0.75, 0.75), 0.0);
	}
	else {
		edge = rand() % 2;
		int yPos = 0;
		if (type == 3) {
			yPos = (rand() % (windowHeight / 2));
		}
		else if (type == 5) {
			yPos = rand() % windowHeight;
		}
		switch (edge) {
		case 0:
			startPosition = glm::vec2(-64, yPos);
			velocity = glm::vec2(150, 0);
			break;
		case 1:
			startPosition = glm::vec2(windowWidth + 64, yPos);
			velocity = glm::vec2(-150, 0);
			break;
		}
		enemy.AddComponent<TransformComponent>(startPosition, glm::vec2(0.5, 0.5), 0.0);
	}
	enemy.AddComponent<RigidBodyComponent>(velocity);
}

void PlaySoundEffect(std::string soundEffectId, int volume) {
	Mix_Chunk* soundEffect = Game::GetInstance().assetManager->GetSoundEffect(soundEffectId);
	if (soundEffect) {
		Mix_VolumeChunk(soundEffect, volume);
		Mix_PlayChannel(-1, soundEffect, 0);
	}
}
/**
 * @brief Returns the current boss health and plays a scream sound once at health = 10.
 *
 * @return int Boss health.
 */
int CheckBossHealth() {
	int bossHealth = Game::GetInstance().registry->GetSystem<GameManagerSystem>().GetBoss().GetComponent<HealthComponent>().health;
	bool condition = true;
	if (bossHealth == 10 && condition) {
		PlaySoundEffect("bossScream", 40);
		condition = false;
	}
	return bossHealth;
}

#endif // !LUABINDING_HPP