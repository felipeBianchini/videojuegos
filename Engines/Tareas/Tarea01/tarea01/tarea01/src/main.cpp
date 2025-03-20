#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Window {
	int width, height, r, g, b;
};

struct Font {
	std::string filename;
	int r, g, b, fontSize;
};

struct Entity {
	std::string label, filename;
	int width, height, posX, posY, vX, vY;
	double angle;
};

int main() {
	std::string filename = "./src/config.txt";
	std::ifstream file(filename);
	if (!file) {
		std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
		return -1;
	}
	Window window;
	Font font;
	std::vector<Entity> entities;
	std::string txtLabel;
	while (file >> txtLabel) {
		if (txtLabel.compare("window") == 0) {
			file >> window.width >> window.height >> window.r >> window.g >> window.b;
		}
		if (txtLabel.compare("font") == 0) {
			file >> font.filename >> font.r >> font.g >> font.b >> font.fontSize;
		}
		if (txtLabel.compare("entity") == 0) {
			Entity entity;
			file >> entity.label >> entity.filename >> entity.width >> entity.height >> entity.posX >> entity.posY
				>> entity.vX >> entity.vY >> entity.angle;
			entities.push_back(entity);
		}
	}

	/*std::cout << window.width << window.height << window.r << window.g << window.b;
	std::cout << font.filename << font.r << font.g << font.b << font.fontSize;
	for (const auto& n : entities) {
		std::cout << n.label << " " << n.filename << " "
			<< n.width << " " << n.height << " "
			<< n.posX << " " << n.posY << " "
			<< n.vX << " " << n.vY << " "
			<< n.angle << std::endl;
	}*/

	return 0;
}