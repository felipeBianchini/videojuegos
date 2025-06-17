#include "Window.hpp"

Window::Window()
{
	this->width = 0;
	this->height = 0;
	this->r = 0;
	this->g = 0;
	this->b = 0;
}

Window::Window(int w, int h, int r, int g, int b) : Window()
{
	this->width = w;
	this->height = h;
	this->r = r;
	this->g = g;
	this->b = b;
}

Window::~Window() {}