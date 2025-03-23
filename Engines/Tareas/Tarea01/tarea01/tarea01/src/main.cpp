#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "game/Game.hpp"
#include "Classes/Entity.hpp"
#include "Classes/Font.hpp"
#include "Classes/Window.hpp"

int main(int argc, char* argv[]) {

	std::string filename = "./src/config.txt";
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
		return -1;
	}

	Window* window = new Window();
	Font* font = new Font();
	std::vector<Entity*> entities;
	std::string txtLabel;

	while (file >> txtLabel) {
		if (txtLabel.compare("window") == 0) {
			file >> window->width >> window->height >> window->r >> window->g >> window->b;
		}
		if (txtLabel.compare("font") == 0) {
			file >> font->filename >> font->r >> font->g >> font->b >> font->fontSize;
		}
		if (txtLabel.compare("entity") == 0) {
			Entity* entity = new Entity();
			std::string label, filename;
			int width, height, imgPosX, imgPosY, velX, velY;
			double angle;

			file >> label >> filename >> width >> height >> imgPosX >> imgPosY
				>> velX >> velY >> angle;

			entity->setLabel(label);
			entity->setFilename(filename);
			entity->setWidth(width);
			entity->setHeight(height);
			entity->setImgPosX(imgPosX);
			entity->setImgPosY(imgPosY);
			entity->setVelocidadX(velX);
			entity->setVelocidadY(velY);
			entity->setAngle(angle);
			entities.push_back(entity);
		}
	}

	Game game(window, font, entities);
	game.init();
	game.run();
	game.destroy();

	return 0;
}