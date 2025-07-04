#include <iostream>
#include "Game/Game.hpp"

int main(int argc, char* argv[]) {
	
	if (argc > 1) {
		std::cout << argv[1] << std::endl;
	}
	Game& game = game.GetInstance();
	game.Init();
	game.Run();
	game.Destroy();
	return 0;
}