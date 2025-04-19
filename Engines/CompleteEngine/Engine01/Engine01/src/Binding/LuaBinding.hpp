#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>

#include "../Game/Game.hpp"

bool IsActionActivated(const std::string& action) {
	return Game::GetInstance().controllerManager->IsActionActivated(action);
}

#endif // !LUABINDING_HPP