#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"

class AnimationSystem : public System {
public:
	AnimationSystem() {
		RequiredComponent<AnimationComponent>();
		RequiredComponent<SpriteComponent>();
	}

	void Update() {
		for (auto entity : GetSystemEntiities()) {
			auto& animation = entity.GetComponent<AnimationComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();

			animation.currentFrame = ((SDL_GetTicks() - animation.startTime)
				* animation.frameSpeedRate / 1000) % animation.numFrames;
			sprite.srcRect.x = animation.currentFrame * sprite.width;
		}
	}
};

#endif // !ANIMATIONSYSTEM_HPP