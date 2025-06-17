#ifndef FONT_HPP
#define FONT_HPP

#include <string>

class Font {
public:
	Font();
	Font(std::string flnm, int f_r, int f_g, int f_b, int fntsz);
	~Font();

	std::string filename;
	int r;
	int g;
	int b;
	int fontSize;
};

#endif // !FONT_HPP
