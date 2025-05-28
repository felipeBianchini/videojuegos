#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP

#include <SDL.h>
#include <string>

/**
 * @brief Component that holds text rendering information.
 *
 * Contains the text string, font identifier, color, and dimensions.
 */
struct TextComponent {
	std::string text;     ///< The string of text to display.
	std::string fontId;   ///< Identifier for the font used to render the text.
	SDL_Color textColor;  ///< Color of the text.
	int width;            ///< Width of the rendered text (pixels).
	int height;           ///< Height of the rendered text (pixels).

	/**
	 * @brief Constructs a TextComponent with optional parameters.
	 *
	 * @param text The text string to display. Default is empty.
	 * @param fontId The font identifier used for rendering. Default is empty.
	 * @param r Red component of text color (0-255). Default 0.
	 * @param g Green component of text color (0-255). Default 0.
	 * @param b Blue component of text color (0-255). Default 0.
	 * @param a Alpha component (opacity) of text color (0-255). Default 0.
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