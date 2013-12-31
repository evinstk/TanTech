#ifndef SURFACE_H
#define SURFACE_H

struct SDL_Surface;

namespace TanTech {

class Window;

class Surface {
public:
	Surface(const char* file_name, const Window& window);
	~Surface();
	void loadImage(const char* file_name, const Window& window);
private:
	SDL_Surface* _surface;
	friend class Texture;

	Surface(const Surface&);
	Surface& operator=(const Surface&);
};

}

#endif
