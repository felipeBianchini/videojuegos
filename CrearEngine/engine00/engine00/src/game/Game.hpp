#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <glm/glm.hpp>
#include <string>

const int FPS = 60;
const int MS_PER_FPS = 1000 / FPS;

class Game {
public:
    Game();
    ~Game();

    void init();
    void run();
    void destroy();

private:
    void processInput();
    void update();
    void render();

    SDL_Window* window;
    SDL_Renderer* renderer;

    size_t windowWidth;
    size_t windowHeight;

    bool isRunning;

    /////////////////////////////////////////////////////////////////////////////////////////

    // Para animaciones

    int mPreviousFrame;
    glm::vec2 velocidad;

    /////////////////////////////////////////////////////////////////////////////////////////

    // Para mostrar imágenes

    SDL_Texture* imgTexture;
    glm::vec2 imgPos;
    size_t imgWidth;
    size_t imgHeight;
    SDL_Rect srcRect;
    double imgAngle;

    /////////////////////////////////////////////////////////////////////////////////////////

    // Para mostrar texto 

    TTF_Font* font;
    int fontSize;
    SDL_Color fontColor;
    std::string msg;
    glm::vec2 msgPos;
    size_t msgWidth;
    size_t msgHeight;
    double msgAngle;
    SDL_Texture* msgTexture;

    /////////////////////////////////////////////////////////////////////////////////////////

};

#endif // GAME_HPP
