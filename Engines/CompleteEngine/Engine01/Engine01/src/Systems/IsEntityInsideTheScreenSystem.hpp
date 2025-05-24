#ifndef ISENTITYINSIDETHESCREENSYSTEM_HPP
#define ISENTITYINSIDETHESCREENSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/IsEntityInsideTheScreenComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"

class IsEntityInsideTheScreenSystem : public System {
public:
    IsEntityInsideTheScreenSystem() {
        RequiredComponent<IsEntityInsideTheScreenComponent>();
        RequiredComponent<TransformComponent>();
        RequiredComponent<SpriteComponent>();
    }

    void Update(int windowWidth, int windowHeight) {
        for (auto entity : GetSystemEntiities()) {
            auto& transform = entity.GetComponent<TransformComponent>();
            auto& insideComponent = entity.GetComponent<IsEntityInsideTheScreenComponent>();
            auto& sprite = entity.GetComponent<SpriteComponent>();
            double posX = transform.position.x + sprite.width * transform.scale.x;
            double posY = transform.position.y + sprite.height * transform.scale.y;
            double w = static_cast<double>(windowWidth);
            double h = static_cast<double>(windowHeight);
            bool fullyInside = posX - sprite.width > 0 && posY > 0 && posX < w && posY < h;
            if (fullyInside) {
                insideComponent.isEntityInsideTheScreen = true;
            }
        }
    }

};

#endif // ISENTITYINSIDETHESCREENSYSTEM_HPP
