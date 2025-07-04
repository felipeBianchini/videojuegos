#ifndef CONTROLLERMANAGER_HPP
#define CONTROLLERMANAGER_HPP
#include <map>
#include <SDL2/SDL.h>
#include <string>
#include <tuple>

/**
 * @brief A manager class for handling keyboard and mouse input.
 * 
 * This class provides a centralized system for managing input events,
 * mapping actions to keys and mouse buttons, and tracking their states.
 * It supports both keyboard and mouse input handling.
 */
class ControllerManager {
public:
    /**
     * @brief Constructs a ControllerManager and initializes input systems.
     */
    ControllerManager();
    
    /**
     * @brief Destroys the ControllerManager and cleans up resources.
     */
    ~ControllerManager();
    
    /**
     * @brief Associates an action name with a keyboard key code.
     * 
     * @param action The name of the action to bind.
     * @param keyCode The SDL key code to associate with the action.
     */
    void AddActionKey(const std::string& action, int keyCode);
    
    /**
     * @brief Registers a key press event.
     * 
     * @param keyCode The SDL key code that was pressed.
     */
    void KeyDown(int keyCode);
    
    /**
     * @brief Registers a key release event.
     * 
     * @param keyCode The SDL key code that was released.
     */
    void KeyUp(int keyCode);
    
    /**
     * @brief Checks if a specific action is currently activated.
     * 
     * @param action The name of the action to check.
     * @return True if the action is currently activated, false otherwise.
     */
    bool IsActionActivated(const std::string& action);
    
    /**
     * @brief Clears all input states and mappings.
     */
    void Clear();
    
    /**
     * @brief Associates a mouse button name with a button code.
     * 
     * @param name The name to assign to the mouse button.
     * @param buttonCode The SDL mouse button code to associate.
     */
    void AddMouseButton(const std::string& name, int buttonCode);
    
    /**
     * @brief Registers a mouse button press event.
     * 
     * @param buttonCode The SDL mouse button code that was pressed.
     */
    void MouseButtonDown(int buttonCode);
    
    /**
     * @brief Registers a mouse button release event.
     * 
     * @param buttonCode The SDL mouse button code that was released.
     */
    void MouseButtonUp(int buttonCode);
    
    /**
     * @brief Checks if a named mouse button is currently pressed.
     * 
     * @param name The name of the mouse button to check.
     * @return True if the mouse button is currently pressed, false otherwise.
     */
    bool IsMouseButtonDown(const std::string& name);
    
    /**
     * @brief Sets the current mouse position.
     * 
     * @param x The x-coordinate of the mouse position.
     * @param y The y-coordinate of the mouse position.
     */
    void SetMousePosition(int x, int y);
    
    /**
     * @brief Gets the current mouse position.
     * 
     * @return A tuple containing the x and y coordinates of the mouse position.
     */
    std::tuple<int, int> GetMousePosition();
    
private:
    /**
     * @brief Maps action names to their corresponding key codes.
     */
    std::map<std::string, int> actionKeyName;
    
    /**
     * @brief Tracks the pressed state of each key code.
     */
    std::map<int, bool> keyDown;
    
    /**
     * @brief Maps mouse button names to their corresponding button codes.
     */
    std::map<std::string, int> mouseButtonName;
    
    /**
     * @brief Tracks the pressed state of each mouse button code.
     */
    std::map<int, bool> mouseButtonDown;
    
    /**
     * @brief The current x-coordinate of the mouse position.
     */
    int mousePosX;
    
    /**
     * @brief The current y-coordinate of the mouse position.
     */
    int mousePosY;
};
#endif // !CONTROLLERMANAGER_HPP