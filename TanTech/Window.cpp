#include "Window.h"
#include "_SDL_System.h"
#include <SDL.h>
#include <stdexcept>

TanTech::Window::Window(const char* title, int w, int h): _window(0) {
	try {
		TanTech::_SDL_System::registerObject(TanTech::_SDL_System::VIDEO);
	}
	catch (std::exception ex) {
		throw ex;
	}
	_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN);
	if (_window == 0) {
		TanTech::_SDL_System::unregisterObject(TanTech::_SDL_System::VIDEO);
		throw std::runtime_error(SDL_GetError());
	}
}

TanTech::Window::Window(const char* title): _window(0) {
	try {
		TanTech::_SDL_System::registerObject(TanTech::_SDL_System::VIDEO);
	}
	catch (std::exception ex) {
		throw ex;
	}
	_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (_window == 0) {
		TanTech::_SDL_System::unregisterObject(TanTech::_SDL_System::VIDEO);
		throw std::runtime_error(SDL_GetError());
	}
}

TanTech::Window::~Window() {
	SDL_DestroyWindow(_window);
	TanTech::_SDL_System::unregisterObject(TanTech::_SDL_System::VIDEO);
}
