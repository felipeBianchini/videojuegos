/**
 * @file SpriteComponent.hpp
 * @brief Component for rendering sprites and textures on entities
 */

#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP
#include <SDL2/SDL.h>
#include <string>

/**
 * @struct SpriteComponent
 * @brief Component that handles sprite rendering and texture display for entities
 * 
 * This component contains all the necessary information to render a sprite,
 * including texture reference, dimensions, source rectangle for sprite sheets,
 * and flip state. It works with the rendering system to display visual
 * representations of entities on screen.
 */
struct SpriteComponent {
    std::string textureId;    ///< Identifier for the texture to be rendered
    int width;                ///< Width of the sprite in pixels
    int height;               ///< Height of the sprite in pixels
    SDL_Rect srcRect;         ///< Source rectangle defining which part of the texture to use
    bool flip = false;        ///< Whether to flip the sprite horizontally during rendering
    
    /**
     * @brief Constructor for SpriteComponent
     * @param textureId Identifier for the texture to be rendered (default: "none")
     * @param width Width of the sprite in pixels (default: 0)
     * @param height Height of the sprite in pixels (default: 0)
     * @param srcRectX X coordinate of the source rectangle in the texture (default: 0)
     * @param srcRectY Y coordinate of the source rectangle in the texture (default: 0)
     * 
     * The constructor automatically sets up the source rectangle using the provided
     * dimensions and coordinates. This is useful for sprite sheets where only a
     * portion of the texture should be displayed.
     */
    SpriteComponent(const std::string& textureId = "none", int width = 0,
                    int height = 0, int srcRectX = 0, int srcRectY = 0) {
        this->textureId = textureId;
        this->width = width;
        this->height = height;
        this->srcRect = {srcRectX, srcRectY, width, height};
    }
};

#endif // SPRITECOMPONENT_HPP