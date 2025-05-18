#ifndef MOVEMENTSYSTEM_HPP
#define MOVEMENTSYSTEM_HPP

#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../ECS/ECS.hpp"

class MovementSystem : public System {
public:
    MovementSystem() {
        RequiredComponent<RigidBodyComponent>();
        RequiredComponent<TransformComponent>();
        RequiredComponent<SpriteComponent>();
    }

    void Update(double dt, int windowHeight, int windowWidth) {
        for (auto entity : GetSystemEntiities()) {
            auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
            auto& transform = entity.GetComponent<TransformComponent>();
            auto& sprite = entity.GetComponent<SpriteComponent>();
            int type = entity.GetComponent<EntityTypeComponent>().entityType;

            double spriteWidth = sprite.width * transform.scale.x;
            double spriteHeight = sprite.height * transform.scale.y;

            double w = static_cast<double>(windowWidth);
            double h = static_cast<double>(windowHeight);
            bool isFullyInside = transform.position.x > 0 && transform.position.x < w;

            transform.position.x += rigidBody.velocity.x * dt;
            transform.position.y += rigidBody.velocity.y * dt;

            if (isFullyInside && type == 3) {
                if (transform.position.x <= 0) {
                    rigidBody.velocity.x *= -1;
                }
                else if (transform.position.x >= w) {
                    transform.position.x = w;
                    rigidBody.velocity.x *= -1;
                }

            }
            if ((type ==  2 || type == 4) && (transform.position.x > w || transform.position.y > h)) {
                entity.Kill();
            }
        }
    }
};

#endif // MOVEMENTSYSTEM_HPP
