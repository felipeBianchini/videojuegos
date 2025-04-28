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
}

// RigidBodyComponent

void SetVelocity(Entity entity, float x, float y) {
	auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
	rigidBody.velocity.x = x;
	rigidBody.velocity.y = y;
}

void GoToScene(const std::string& sceneName) {
	Game::GetInstance().sceneManager->SetNextScene(sceneName);
	Game::GetInstance().sceneManager->StopScene();
}

void GoToNextScene() {
	Game::GetInstance().registry->GetSystem<GameManagerSystem>().GoToNextScene(Game::GetInstance().lua);
}

#endif // !LUABINDING_HPP