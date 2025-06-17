#include "Entity.hpp"

Entity::Entity()
{
    this->label = "";
    this->filename = "";
    this->width = 0;
    this->height = 0;
    this->angle = 0.0;
    this->srcRect = { 0, 0, 0, 0 };
    this->imgTexture = nullptr;
}

Entity::Entity(std::string lbl, std::string flnm, int w, int h, int psX, int psY, int vx, int vy, int ang) : Entity()
{
    this->label = lbl;
    this->filename = flnm;
    this->width = w;
    this->height = h;
    this->angle = ang;
    this->imgPos.x = psX;
    this->imgPos.y = psY;
    this->velocidad.x = vx;
    this->velocidad.y = vy;

}

std::string Entity::getLabel()
{
    return this->label;
}

std::string Entity::getFilename()
{
    return this->filename;
}

int Entity::getWidth()
{
    return this->width;
}

int Entity::getHeight()
{
    return this->height;
}

double Entity::getImgPosX()
{
    return imgPos.x;
}

double Entity::getImgPosY()
{
    return imgPos.y;
}

double Entity::getVelocidadX()
{
    return velocidad.x;
}

double Entity::getVelocidadY()
{
    return velocidad.y;
}

double Entity::getAngle()
{
    return this->angle;
}

SDL_Rect& Entity::getSrcRect()
{
    return this->srcRect;
}

SDL_Texture* Entity::getTexture()
{
    return this->imgTexture;
}

void Entity::setLabel(std::string& lbl)
{
    this->label = lbl;
}

void Entity::setFilename(std::string& flnm)
{
    this->filename = flnm;
}

void Entity::setWidth(int w)
{
    this->width = w;
}

void Entity::setHeight(int h)
{
    this->height = h;
}

void Entity::setImgPosX(double posX)
{
    this->imgPos.x = posX;
}

void Entity::setImgPosY(double posY)
{
    this->imgPos.y = posY;
}

void Entity::setVelocidadX(double vX)
{
    this->velocidad.x = vX;
}

void Entity::setVelocidadY(double vY)
{
    this->velocidad.y = vY;
}

void Entity::setAngle(double ang)
{
    this->angle = ang;
}

void Entity::setSrcRect(SDL_Rect rect)
{
    this->srcRect = rect;
}

void Entity::setTexture(SDL_Texture* texture)
{
    this->imgTexture = texture;
}

Entity::~Entity() {
    SDL_DestroyTexture(this->imgTexture);
}
