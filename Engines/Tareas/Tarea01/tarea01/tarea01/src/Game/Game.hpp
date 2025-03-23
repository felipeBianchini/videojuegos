#ifndef GAME_HPP
#define GAME_HPP

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <glm/glm.hpp> 
#include <string>
#include <vector>

#include "../Classes/Entity.hpp"
#include "../Classes/Font.hpp"
#include "../Classes/Window.hpp"

const int FPS = 60;
const int MS_PER_FPS = 1000 / FPS;

class Game {
public:
    Game();
    Game(Window* window, Font* font, std::vector<Entity*> entities);
    ~Game();

    void init();
    void run();
    void destroy();

private:
    void processInput();
    void update();
    void render();

    Window* windw;
    Font* fnt;
    std::vector<Entity*> entities;

    SDL_Window* window;
    SDL_Renderer* renderer;

    bool isRunning;
    bool keepMoving;

    /////////////////////////////////////////////////////////////////////////////////////////

    // Para animaciones

    int mPreviousFrame;

    /////////////////////////////////////////////////////////////////////////////////////////

    // Para mostrar texto 

    TTF_Font* font;
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
