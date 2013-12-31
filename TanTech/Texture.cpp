#include "Texture.h"
#include "Renderer.h"
#include "Surface.h"
#include "_SDL_System.h"
#include <SDL_render.h>

TanTech::Texture::Texture(const Renderer& renderer, const Surface& surface): _texture(0) {
	try {
		TanTech::_SDL_System::registerObject(TanTech::_SDL_System::VIDEO);
	}
	catch (std::runtime_error ex) {
		throw ex;
	}
	_texture = SDL_CreateTextureFromSurface(renderer._renderer, surface._surface);
	if (_texture == 0) {
		TanTech::_SDL_System::unregisterObject(TanTech::_SDL_System::VIDEO);
		throw std::runtime_error(SDL_GetError());
	}
}

TanTech::Texture::~Texture() {
	SDL_DestroyTexture(_texture);
	TanTech::_SDL_System::unregisterObject(TanTech::_SDL_System::VIDEO);
}
