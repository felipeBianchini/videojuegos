#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>

#include "../Systems/GameManagerSystem.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Game/Game.hpp"
#include "../ECS/ECS.hpp"

void AddScriptComponent(Entity entity, std::string path);
void AddTransformAndRigidBodyComponent(Entity enemy, int windowHeigth, int windowWidth, int type);

bool IsActionActivated(const std::string& action) {
	return Game::GetInstance().controllerManager->IsActionActivated(action);
};

void SetVelocity(Entity entity, float x, float y) {
	auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
	rigidBody.velocity.x = x;
	rigidBody.velocity.y = y;
};

void GoToScene(const std::string& sceneName) {
	Game::GetInstance().sceneManager->SetNextScene(sceneName);
	Game::GetInstance().sceneManager->StopScene();
};

void GoToNextScene() {
	Game::GetInstance().registry->GetSystem<GameManagerSystem>().GoToNextScene(Game::GetInstance().lua);
};

void BulletFactory(double playerX, double playerY) {
	Entity bullet = Game::GetInstance().registry->CreateEntity();
	bullet.AddComponent<CircleColliderComponent>(32, 32, 32);
	bullet.AddComponent<RigidBodyComponent>(glm::vec2(0, -400));
	bullet.AddComponent<SpriteComponent>("bullet", 64, 64, 0, 0);
	bullet.AddComponent<TransformComponent>(glm::vec2(playerX + 10, playerY + 10), glm::vec2(0.5, 0.5), 0.0);
	bullet.AddComponent<EntityTypeComponent>(2);
}

void EnemyBulletsFactory(double enemyX, double enemyY) {
	Entity enemyBullet = Game::GetInstance().registry->CreateEntity();
	enemyBullet.AddComponent<CircleColliderComponent>(25, 14, 42);
	enemyBullet.AddComponent<RigidBodyComponent>(glm::vec2(0, 400));
	enemyBullet.AddComponent<SpriteComponent>("enemy1projectile", 14, 42, 0, 0);
	enemyBullet.AddComponent<TransformComponent>(glm::vec2(enemyX + 10, enemyY + 10), glm::vec2(1.0, 1.0), 0.0);
	enemyBullet.AddComponent<EntityTypeComponent>(4);
}

void Enemy1Factory(int windowHeight, int windowWidth) {
	Entity enemy1 = Game::GetInstance().registry->CreateEntity();
	enemy1.AddComponent<CircleColliderComponent>(64, 64, 64);
	enemy1.AddComponent<SpriteComponent>("enemy1", 128, 128, 0, 0);
	enemy1.AddComponent<HealthComponent>(5);
	enemy1.AddComponent<ScoreComponent>(100);
	enemy1.AddComponent<EntityTypeComponent>(3);
	AddScriptComponent(enemy1, "./assets/scripts/enemy1.lua");
	AddTransformAndRigidBodyComponent(enemy1, windowHeight, windowWidth, 4);
}

void Enemy2Factory(int windowHeight, int windowWidth) {
	Entity enemy2 = Game::GetInstance().registry->CreateEntity();
	enemy2.AddComponent<CircleColliderComponent>(64, 64, 64);
	enemy2.AddComponent<SpriteComponent>("enemy2", 128, 128, 0, 0);
	enemy2.AddComponent<HealthComponent>(2);
	enemy2.AddComponent<ScoreComponent>(50);
	enemy2.AddComponent<EntityTypeComponent>(5);
	AddTransformAndRigidBodyComponent(enemy2, windowHeight, windowWidth, 5);
}

void AddScriptComponent(Entity entity, std::string path) {
	sol::state& lua = Game::GetInstance().lua;
	sol::function nil = sol::nil;
	lua.script_file(path);
	sol::function updateEnemy1Position = Game::GetInstance().lua["updateEnemy1Position"];
	entity.AddComponent<ScriptComponent>(nil, nil, nil, updateEnemy1Position, nil, nil);
}

void AddTransformAndRigidBodyComponent(Entity enemy, int windowHeigth, int windowWidth, int type) {
	int edge = rand() % 2;
	glm::vec2 startPosition;
	glm::vec2 velocity;
	int yPos = 0;
	if (type == 3) {
		yPos = rand() % (windowHeigth / 2);
	}
	else if (type == 5) {
		yPos = rand() % windowHeigth;
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
	enemy.AddComponent<RigidBodyComponent>(velocity);
	enemy.AddComponent<TransformComponent>(startPosition, glm::vec2(0.5, 0.5), 0.0);
}

#endif // !LUABINDING_HPP