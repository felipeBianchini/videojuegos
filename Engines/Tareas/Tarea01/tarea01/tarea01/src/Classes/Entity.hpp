#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <glm/glm.hpp>
#include <SDL.h>
#include <string>

class Entity {
public:
    Entity();
    Entity(std::string lbl, std::string flnm, int w, int h, int psX, int psY, int vx, int vy, int ang);
    ~Entity();

    std::string getLabel();
    std::string getFilename();
    int getWidth();
    int getHeight();
    double getImgPosX();
    double getImgPosY();
    double getVelocidadX();
    double getVelocidadY();
    double getAngle();
    SDL_Rect& getSrcRect();
    SDL_Texture* getTexture();

    void setLabel(std::string& lbl);
    void setFilename(std::string& flnm);
    void setWidth(int w);
    void setHeight(int h);
    void setImgPosX(double posX);
    void setImgPosY(double posY);
    void setVelocidadX(double vX);
    void setVelocidadY(double vY);
    void setAngle(double ang);
    void setSrcRect(SDL_Rect rect);
    void setTexture(SDL_Texture* texture);

private:
    std::string label;
    std::string filename;
    int width;
    int height;
    glm::vec2 imgPos;
    glm::vec2 velocidad;
    double angle;
    SDL_Rect srcRect;
    SDL_Texture* imgTexture;
};

#endif // !ENTITY_HPP
