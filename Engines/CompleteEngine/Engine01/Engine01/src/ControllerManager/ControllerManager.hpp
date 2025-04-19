#ifndef CONTROLLERMANAGER_HPP
#define CONTROLLERMANAGER_HPP

#include <map>
#include <SDL.h>
#include <string>

class ControllerManager {
public:
	ControllerManager();
	~ControllerManager();

	void AddActionKey(const std::string& action, int keyCode);
	void KeyDown(int keyCode);
	void KeyUp(int keyCode);
	bool IsActionActivated(const std::string& action);
	void Clear();
private:
	std::map<std::string, int> actionKeyName;
	std::map<int, bool> keyDown;
};

#endif // !CONTROLLERMANAGER_HPP