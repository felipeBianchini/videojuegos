#ifndef CAMERAMOVEMENTSYSTEM_HPP
#define CAMERAMOVEMENTSYSTEM_HPP

#include <SDL2/SDL.h>
#include "../Components/CameraFollowComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"

class CameraMovementSystem : public System {
public:
	CameraMovementSystem() {
		RequiredComponent<CameraFollowComponent>();
		RequiredComponent<TransformComponent>();
	}

	void Update(SDL_Rect& camera) {
		for (auto entity : GetSystemEntiities()) {
			const auto& transform = entity.GetComponent<TransformComponent>();
			if (transform.position.x + (camera.w / 2) < 
				static_cast<float>(Game::GetInstance().mapWidth)) {
				camera.x = static_cast<int>(transform.position.x) - (camera.w / 2);
			}
			if (transform.position.y + (camera.h / 2) <
				static_cast<float>(Game::GetInstance().mapHeigth)) {
				camera.y = static_cast<int>(transform.position.y) - (camera.h / 2);
			}

			camera.x = camera.x < 0 ? 0 : camera.x;
			camera.y = camera.y < 0 ? 0 : camera.y;
		}
	}
};

#endif // !CAMERAMOVEMENTSYSTEM_HPP