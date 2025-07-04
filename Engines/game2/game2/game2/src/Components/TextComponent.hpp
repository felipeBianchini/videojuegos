#ifndef TEXTCOMPONENT_HPP
#define TEXTCOMPONENT_HPP

#include <SDL2/SDL.h>
#include <string>

struct TextComponent {
	std::string text;
	std::string fontId;
	SDL_Color textColor;
	int width;
	int height;

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