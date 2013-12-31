#include "Surface.h"
#include "Window.h"
#include "_SDL_System.h"
#include <stdexcept>
#include <SDL_video.h>
#include <SDL_image.h>

TanTech::Surface::Surface(const char* file_name, const Window& window): _surface(0) {
	try {
		TanTech::_SDL_System::registerObject(TanTech::_SDL_System::VIDEO);
	}
	catch (std::runtime_error ex) {
		throw ex;
	}
	try {
		loadImage(file_name, window);
	}
	catch (std::runtime_error ex) {
		throw ex;
	}
}

TanTech::Surface::~Surface() {
	SDL_FreeSurface(_surface);
	TanTech::_SDL_System::unregisterObject(TanTech::_SDL_System::VIDEO);
}

void TanTech::Surface::loadImage(const char* file_name, const Window& window) {
	if (_surface != 0) SDL_FreeSurface(_surface);
	SDL_Surface* loaded_image = IMG_Load(file_name);
	if (loaded_image != 0) {
		_surface = SDL_ConvertSurface(loaded_image, SDL_GetWindowSurface(window._window)->format, 0);
		SDL_FreeSurface(loaded_image);
		if (_surface != 0) return;
		throw std::runtime_error(SDL_GetError());
	}
	throw std::runtime_error(SDL_GetError());
}
