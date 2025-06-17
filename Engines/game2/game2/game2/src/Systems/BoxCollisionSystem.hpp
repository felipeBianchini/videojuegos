#ifndef BOXCOLLISIONSYSTEM_HPP
#define BOXCOLLISIONSYSTEM_HPP

#include <iostream>

#include "../Components/BoxColliderComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../ECS/ECS.hpp"

class BoxCollisionSystem : public System {
private:
	bool CheckCollision(float aX, float aY, float aW, float aH, float bX, float bY, float bW, float bH) {
		return(
			aX < bX + bW &&
			aX + aW > bX &&
			aY < bY + bH &&
			aY + aH > bY
			);
	}
public:
	BoxCollisionSystem() {
		RequiredComponent<BoxColliderComponent>();
		RequiredComponent<TransformComponent>();
	}

	void Update(sol::state& lua) {
		auto entities = GetSystemEntiities();
		for (auto i = entities.begin(); i != entities.end(); i++) {
			Entity a = *i;
			const auto& aCollider = a.GetComponent<BoxColliderComponent>();
			const auto& aTranform = a.GetComponent<TransformComponent>();
			for (auto j = i; j != entities.end(); j++) {
				Entity b = *j;
				if (a == b) {
					continue;
				}

				const auto& bCollider = b.GetComponent<BoxColliderComponent>();
				const auto& bTranform = b.GetComponent<TransformComponent>();

				bool collision = CheckCollision(
					aTranform.position.x, aTranform.position.y, static_cast<float>(aCollider.width), static_cast<float>(aCollider.heigth),
					bTranform.position.x, bTranform.position.y, static_cast<float>(bCollider.width), static_cast<float>(bCollider.heigth)
				);

				if (collision) {
					if (a.HasComponent<ScriptComponent>()) {
						const auto& script = a.GetComponent<ScriptComponent>();
						if (script.onCollision != sol::nil) {
							lua["this"] = a;
							script.onCollision(b);
						}
					}
					if (b.HasComponent<ScriptComponent>()) {
						const auto& script = b.GetComponent<ScriptComponent>();
						if (script.onCollision != sol::nil) {
							lua["this"] = b;
							script.onCollision(a);
						}
					}
				}
			}
		}
	}
};

#endif // !BOXCOLLISIONSYSTEM_HPP