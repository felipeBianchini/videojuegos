#ifndef CLICKEVENT_HPP
#define CLICKEVENT_HPP
#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"

/**
 * @brief An event class representing a mouse click event.
 * 
 * This class encapsulates information about a mouse click event,
 * including the button that was clicked and the position where
 * the click occurred.
 */
class ClickEvent : public Event {
public:
    /**
     * @brief The code of the mouse button that was clicked.
     */
    int buttonCode;
    
    /**
     * @brief The x-coordinate of the click position.
     */
    int posX;
    
    /**
     * @brief The y-coordinate of the click position.
     */
    int posY;
    
    /**
     * @brief Constructs a ClickEvent with specified button and position.
     * 
     * @param buttonCode The code of the mouse button that was clicked. Defaults to 0.
     * @param posX The x-coordinate of the click position. Defaults to 0.
     * @param posY The y-coordinate of the click position. Defaults to 0.
     */
    ClickEvent(int buttonCode = 0, int posX = 0, int posY = 0) {
        this->buttonCode = buttonCode;
        this->posX = posX;
        this->posY = posY;
    }
};
#endif // !CLICKEVENT_HPP