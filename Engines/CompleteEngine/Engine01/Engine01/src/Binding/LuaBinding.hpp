#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>

#include "../Systems/GameManagerSystem.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Game/Game.hpp"
#include "../ECS/ECS.hpp"

// Controles

bool IsActionActivated(const std::string& action) {
	return Game::GetInstance().controllerManager->IsActionActivated(action);
};

// RigidBodyComponent

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
	std::cout << "bulletfactory" << std::endl;
	Entity bullet = Game::GetInstance().registry->CreateEntity();
	bullet.AddComponent<CircleColliderComponent>(10, 20, 20);
	bullet.AddComponent<RigidBodyComponent>(glm::vec2(0, -200));
	bullet.AddComponent<SpriteComponent>("bullet", 64, 64, 0, 0);
	bullet.AddComponent<TransformComponent>(glm::vec2(playerX + 10, playerY + 10), glm::vec2(0.5, 0.5), 0.0);
	bullet.AddComponent<EntityTypeComponent>(2);
}

#endif // !LUABINDING_HPP