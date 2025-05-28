#ifndef CONTROLLERMANAGER_HPP
#define CONTROLLERMANAGER_HPP

#include <map>
#include <SDL.h>
#include <string>
#include <tuple>

/**
 * @class ControllerManager
 * @brief Manages input from keyboard and mouse.
 *
 * This class provides an abstraction for handling input actions mapped to keys and mouse buttons.
 * It supports querying the current state of keys and mouse buttons, as well as tracking the mouse position.
 */
class ControllerManager {
public:
	/**
	 * @brief Constructs a new ControllerManager object.
	 */
	ControllerManager();
	/**
	 * @brief Destroys the ControllerManager object.
	 */
	~ControllerManager();
	/**
	 * @brief Maps an action name to a keyboard key code.
	 * @param action The name of the action.
	 * @param keyCode The SDL key code to map.
	 */
	void AddActionKey(const std::string& action, int keyCode);
	/**
	 * @brief Marks a key as pressed.
	 * @param keyCode The SDL key code.
	 */
	void KeyDown(int keyCode);
	/**
	 * @brief Marks a key as released.
	 * @param keyCode The SDL key code.
	 */
	void KeyUp(int keyCode);
	/**
	 * @brief Checks if a mapped action is currently active (key pressed).
	 * @param action The name of the action.
	 * @return True if the action is active, false otherwise.
	 */
	bool IsActionActivated(const std::string& action);
	/**
	 * @brief Clears all key and mouse input states.
	 */
	void Clear();
	/**
	 * @brief Maps a mouse button name to a button code.
	 * @param name The name of the mouse button action.
	 * @param buttonCode The SDL mouse button code to map.
	 */
	void AddMouseButton(const std::string& name, int buttonCode);
	/**
	 * @brief Marks a mouse button as pressed.
	 * @param buttonCode The SDL mouse button code.
	 */
	void MouseButtonDown(int buttonCode);
	/**
	 * @brief Marks a mouse button as released.
	 * @param buttonCode The SDL mouse button code.
	 */
	void MouseButtonUp(int buttonCode);
	/**
	 * @brief Checks if a mapped mouse button is currently pressed.
	 * @param name The name of the mouse button.
	 * @return True if the button is pressed, false otherwise.
	 */
	bool IsMouseButtonDown(const std::string& name);
	/**
	 * @brief Sets the current mouse position.
	 * @param x X-coordinate of the mouse.
	 * @param y Y-coordinate of the mouse.
	 */
	void SetMousePosition(int x, int y);
	/**
	 * @brief Gets the current mouse position.
	 * @return A tuple containing the x and y coordinates of the mouse.
	 */
	std::tuple<int, int> GetMousePosition();

private:
	std::map<std::string, int> actionKeyName;      ///< Maps action names to key codes.
	std::map<int, bool> keyDown;                   ///< Tracks which keys are currently pressed.
	std::map<std::string, int> mouseButtonName;    ///< Maps mouse button names to button codes.
	std::map<int, bool> mouseButtonDown;           ///< Tracks which mouse buttons are currently pressed.
	int mousePosX;                                 ///< Current X position of the mouse.
	int mousePosY;                                 ///< Current Y position of the mouse.
};

#endif // !CONTROLLERMANAGER_HPP