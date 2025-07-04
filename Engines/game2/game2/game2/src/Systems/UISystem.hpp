/**
 * @file UISystem.hpp
 * @brief System for handling user interface interactions and click events
 */

#ifndef UISYSTEM_HPP
#define UISYSTEM_HPP
#include <SDL2/SDL.h>
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
 * @brief System responsible for handling user interface interactions
 * 
 * This system manages clickable UI elements, particularly text-based buttons
 * and interactive elements. It processes click events and determines if they
 * intersect with any clickable entities, triggering appropriate script callbacks
 * when interactions occur.
 */
class UISystem : public System {
public:
    /**
     * @brief Constructor for UISystem
     * 
     * Initializes the UI system and sets up the required component types.
     * Only entities with ClickableComponent, TextComponent, and TransformComponent
     * will be processed by this system.
     */
    UISystem() {
        RequiredComponent<ClickableComponent>();
        RequiredComponent<TextComponent>();
        RequiredComponent<TransformComponent>();
    }
    
    /**
     * @brief Subscribes to click events from the event manager
     * 
     * Sets up the event subscription so that this system will receive
     * ClickEvent notifications and handle them through the OnClickEvent callback.
     * 
     * @param eventManager Event manager to subscribe to for click events
     */
    void SubscribeToClickEvent(std::unique_ptr<EventManager>& eventManager) {
        eventManager->SubscribeToEvent<ClickEvent, UISystem>(this, &UISystem::OnClickEvent);
    }
    
    /**
     * @brief Handles click events and determines if they intersect with UI elements
     * 
     * When a click event occurs, this method checks all clickable entities to see
     * if the click position intersects with their bounding rectangles. For entities
     * that are clicked and have a ScriptComponent with an onClick handler, the
     * script callback is executed.
     * 
     * @param e Click event containing the position coordinates of the click
     */
    void OnClickEvent(ClickEvent& e) {
        for (auto entity : GetSystemEntiities()) {
            const auto& text = entity.GetComponent<TextComponent>();
            const auto& transform = entity.GetComponent<TransformComponent>();
            
            // Check if click position is within the entity's bounding rectangle
            if (transform.position.x < e.posX
                && e.posX < transform.position.x + text.width
                && transform.position.y < e.posY
                && e.posY < transform.position.y + text.height) {
                
                // Execute script callback if entity has onClick handler
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