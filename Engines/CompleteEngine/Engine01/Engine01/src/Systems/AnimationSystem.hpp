#ifndef ANIMATIONSYSTEM_HPP
#define ANIMATIONSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/EntityTypeComponent.hpp"

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

            int elapsedFrames = ((SDL_GetTicks() - animation.startTime) * animation.frameSpeedRate / 1000);
            if (elapsedFrames >= animation.numFrames) {
                if (entity.HasComponent<EntityTypeComponent>()) {
                    int type = entity.GetComponent<EntityTypeComponent>().entityType;
                    if (type == 12) {
                        entity.Kill();
                        continue;
                    }
                }
            }
            else {
                animation.currentFrame = elapsedFrames;
                sprite.srcRect.x = animation.currentFrame * sprite.width;
            }
        }
    }

};

#endif // !ANIMATIONSYSTEM_HPP