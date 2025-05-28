#ifndef UISYSTEM_HPP
#define UISYSTEM_HPP

#include <SDL.h>
#include <memory>
#include <string>

#include "../ECS/ECS.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/ClickableComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/ClickEvent.hpp"

/**
 * @class UISystem
 * @brief A system for handling user interface interactions within an Entity-Component-System (ECS) architecture.
 *
 * This system manages entities with clickable UI elements, processing click events to trigger associated scripts.
 * It requires entities to have ClickableComponent, TextComponent, and TransformComponent.
 */
class UISystem : public System {
public:
	/**
	 * @brief Constructor for the UISystem.
	 *
	 * Initializes the system and specifies the required components for entities it will manage.
	 */
	UISystem() {
		RequiredComponent<ClickableComponent>();
		RequiredComponent<TextComponent>();
		RequiredComponent<TransformComponent>();
	}
	/**
	 * @brief Subscribes the system to click events via the event manager.
	 *
	 * @param eventManager A unique pointer to the EventManager instance to subscribe to.
	 */
	void SubscribeToClickEvent(std::unique_ptr<EventManager>& eventManager) {
		eventManager->SubscribeToEvent<ClickEvent, UISystem>(this, &UISystem::OnClickEvent);
	}
	/**
	 * @brief Handles click events for UI entities.
	 *
	 * Checks if a click event occurs within the bounds of an entity's UI component and triggers
	 * the associated script's onClick function if available.
	 *
	 * @param e The ClickEvent containing the click position (posX, posY).
	 */
	void OnClickEvent(ClickEvent& e) {
		for (auto entity : GetSystemEntiities()) {
			const auto& text = entity.GetComponent<TextComponent>();
			const auto& transform = entity.GetComponent<TransformComponent>();
			if (transform.position.x < e.posX 
				&& e.posX < transform.position.x + text.width 
				&& transform.position.y < e.posY 
				&& e.posY < transform.position.y + text.height) {
				if (entity.HasComponent<ScriptComponent>()) {
					const auto& script = entity.GetComponent<ScriptComponent>();
					if (script.onClick != sol::nil) {
						script.onClick();
					}
				}
			}
		}
	}
};

#endif // !UISYSTEM_HPP