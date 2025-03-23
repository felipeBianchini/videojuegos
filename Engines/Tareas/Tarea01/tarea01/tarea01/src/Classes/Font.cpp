#include "Font.hpp"

Font::Font()
{
	this->filename = "";
	this->r = 0;
	this->g = 0;
	this->b = 0;
	this->fontSize = 0;
}

Font::Font(std::string flnm, int f_r, int f_g, int f_b, int fntsz) : Font()
{
	this->filename = flnm;
	this->r = f_r;
	this->g = f_g;
	this->b = f_b;
	this->fontSize = fntsz;
}

Font::~Font() {}