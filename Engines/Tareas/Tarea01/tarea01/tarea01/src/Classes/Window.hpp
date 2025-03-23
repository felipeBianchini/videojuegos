#ifndef WINDOW_HPP
#define WINDOW_HPP

class Window {
public:
	Window();
	Window(int w, int h, int r, int g, int b);
	~Window();
	int width;
	int height;
	int r;
	int g;
	int b;
};

#endif // !WINDOW_HPP
