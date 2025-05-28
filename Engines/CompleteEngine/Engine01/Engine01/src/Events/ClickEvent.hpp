#ifndef CLICKEVENT_HPP
#define CLICKEVENT_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"

/**
 * @class ClickEvent
 * @brief Represents a mouse click event in the ECS event system.
 *
 * This event is dispatched when a mouse button is clicked. It stores the button code
 * as well as the x and y coordinates of the cursor at the time of the click.
 */
class ClickEvent : public Event {
public:
    /**
     * @brief The mouse button code (e.g., SDL_BUTTON_LEFT).
     */
    int buttonCode;

    /**
     * @brief The X coordinate of the mouse cursor during the click.
     */
    int posX;

    /**
     * @brief The Y coordinate of the mouse cursor during the click.
     */
    int posY;

    /**
     * @brief Constructs a new ClickEvent with the given button code and position.
     *
     * @param buttonCode The code of the button that was clicked.
     * @param posX The X coordinate of the click position.
     * @param posY The Y coordinate of the click position.
     */
    ClickEvent(int buttonCode = 0, int posX = 0, int posY = 0) {
        this->buttonCode = buttonCode;
        this->posX = posX;
        this->posY = posY;
    }
};

#endif // !CLICKEVENT_HPP
