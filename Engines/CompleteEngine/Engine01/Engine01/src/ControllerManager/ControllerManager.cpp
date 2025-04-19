#include "ControllerManager.hpp"

#include <iostream>

ControllerManager::ControllerManager()
{
	std::cout << "[ControllerManager] Se ejecuta constructor" << std::endl;
}

ControllerManager::~ControllerManager()
{
	std::cout << "[ControllerManager] Se ejecuta destructor" << std::endl;
}

void ControllerManager::AddActionKey(const std::string& action, int keyCode)
{
	actionKeyName.emplace(action, keyCode);
	keyDown.emplace(keyCode, false);
}

void ControllerManager::KeyDown(int keyCode)
{
	auto it = keyDown.find(keyCode);
	if (it != keyDown.end()) {
		keyDown[keyCode] = true;
	}
}

void ControllerManager::KeyUp(int keyCode)
{
	auto it = keyDown.find(keyCode);
	if (it != keyDown.end()) {
		keyDown[keyCode] = false;
	}
}

bool ControllerManager::IsActionActivated(const std::string& action)
{
	auto it = actionKeyName.find(action);
	if (it != actionKeyName.end()) {
		int keyCode = actionKeyName[action];
		return keyDown[keyCode];
	}
	return false;
}

void ControllerManager::Clear()
{
	actionKeyName.clear();
	keyDown.clear();
}
