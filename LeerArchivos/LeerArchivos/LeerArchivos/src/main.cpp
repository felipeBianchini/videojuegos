#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Nombres {
	std::string nombre;
	std::string apellido;
};

int main() {
	std::string filename = "nombres.txt";
	std::ifstream file(filename);
	std::vector<Nombres> nombres;
	Nombres nombre;
	while (file >> nombre.nombre >> nombre.apellido) {
		nombres.push_back(nombre);
	}
	for (const auto& n : nombres) {
		std::cout << n.nombre << " " << n.apellido << std::endl;
	}
	return 0;
}