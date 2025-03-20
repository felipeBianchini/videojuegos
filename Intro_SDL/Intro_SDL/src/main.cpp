#include <iostream>
#include <SDL.h>


int main(int argc, char* argv[]) {

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	size_t width = 800;
	size_t height = 600;

	bool isRunning = true;

	SDL_Rect rect = {
		// coords
		(width / 2) - 25,
		(height / 2) - 25,
		// ancho y alto
		50,
		50
	};

	// Inicializaci�n de SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Error inicializando SDL!" << std::endl;
		return -1;
	}

	window = SDL_CreateWindow(
		// Titulo ventana
		"Tarea 01: Intro a SDL",
		// Posicion x en la pantalla (para que aparezca centrada)
		SDL_WINDOWPOS_CENTERED,
		// Posicion en y en la pantalla
		SDL_WINDOWPOS_CENTERED,
		// Ancho
		width,
		// Alto
		height,
		// Flags https://wiki.libsdl.org/SDL2/SDL_WindowFlags
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
	);

	if (window == NULL) {
		std::cerr << "Error creando ventana!" << std::endl;
		return -1;
	}

	renderer = SDL_CreateRenderer(
		window,
		-1,
		// Flags https://wiki.libsdl.org/SDL2/SDL_RendererFlags
		0
	);

	if (renderer == NULL) {
		std::cerr << "Error creando renderer!" << std::endl;
		return -1;
	}

	while (isRunning) {
		// Registra los datos de un evento
		SDL_Event sdlEvent;

		// Saca de la cola de eventos de SDL un evento pendiente y lo almacena en el registro
		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
			case SDL_QUIT:			// Se cerr� la ventana
				isRunning = false;
				break;
			case SDL_KEYDOWN:		// Se presion� escape
				if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
					isRunning = false;
				}
				break;
			default:
				break;
			}
		}

		// Set color para dibujar
		if (SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255) != 0) {
			std::cerr << "Error en SDL_SetRenderDrawColor!" << std::endl;
			return -1;
		}
		// Limpia ventana con color pre establecido
		if (SDL_RenderClear(renderer) != 0) {
			std::cerr << "Error en SDL_RenderClear!" << std::endl;
			return -1;
		}

		if (SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255) != 0) {
			std::cerr << "Error en SDL_SetRenderDrawColor!" << std::endl;
			return -1;
		}

		if (SDL_RenderFillRect(renderer, &rect) != 0) {
			std::cerr << "Error en SDL_RenderFillRect!" << std::endl;
			return -1;
		}
		// Actualiza la ventana
		SDL_RenderPresent(renderer);
	}

	// Liberar memoria
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}