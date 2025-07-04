#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP
#include <SDL2/SDL.h>
#include <string>

/**
 * @brief A component that holds text rendering information.
 * 
 * This structure represents a text component used for rendering text
 * in a graphics system, containing the text content, font information,
 * color data, and dimensions.
 */
struct TextComponent {
    /**
     * @brief The text string to be rendered.
     */
    std::string text;
    
    /**
     * @brief The identifier of the font to use for rendering.
     */
    std::string fontId;
    
    /**
     * @brief The color of the text using SDL color format.
     */
    SDL_Color textColor;
    
    /**
     * @brief The width of the rendered text in pixels.
     */
    int width;
    
    /**
     * @brief The height of the rendered text in pixels.
     */
    int height;
    
    /**
     * @brief Constructs a TextComponent with customizable text, font, and color properties.
     * 
     * @param text The text string to display. Defaults to empty string.
     * @param fontId The identifier for the font to use. Defaults to empty string.
     * @param r The red component of the text color (0-255). Defaults to 0.
     * @param g The green component of the text color (0-255). Defaults to 0.
     * @param b The blue component of the text color (0-255). Defaults to 0.
     * @param a The alpha component of the text color (0-255). Defaults to 0.
     */
    TextComponent(const std::string& text = "", const std::string& fontId = "", uint8_t r = 0, uint8_t g = 0, uint8_t b = 0, uint8_t a = 0) {
        this->text = text;
        this->fontId = fontId;
        this->textColor.r = r;
        this->textColor.g = g;
        this->textColor.b = b;
        this->textColor.a = a;
        this->width = 0;
        this->height = 0;
    }
};
#endif // !TEXTCOMPONENT_HPP