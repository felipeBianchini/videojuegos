#ifndef UISYSTEM_HPP
#define UISYSTEM_HPP

#include <SDL.h>
#include <memory>
#include <string>

#include "../ECS/ECS.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/ClickableComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/ClickEvent.hpp"

class UISystem : public System {
public:
	UISystem() {
		RequiredComponent<ClickableComponent>();
		RequiredComponent<TextComponent>();
		RequiredComponent<TransformComponent>();
	}
	void SubscribeToClickEvent(std::unique_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<ClickEvent, UISystem>(this, &UISystem::OnClickEvent);
	}
	void OnClickEvent(ClickEvent& e) {
		for (auto entity : GetSystemEntiities()) {
			const auto& text = entity.GetComponent<TextComponent>();
			const auto& transform = entity.GetComponent<TransformComponent>();
			if (transform.position.x < e.posX 
				&& e.posX < transform.position.x + text.width 
				&& transform.position.y < e.posY 
				&& e.posY < transform.position.y + text.height) {
				std::cout << "Se dio click sobre la entidad" << entity.GetId() << std::endl;
			}
		}
	}
};

#endif // !UISYSTEM_HPP