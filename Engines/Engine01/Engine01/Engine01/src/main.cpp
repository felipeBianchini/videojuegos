#include <iostream>
#include "Game/Game.hpp"

int main(int argc, char* argv[]) {
	Game& game = game.GetInstance();
	game.Init();
	game.Run();
	game.Destroy();
	return 0;
}