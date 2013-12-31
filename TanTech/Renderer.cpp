#include "Renderer.h"
#include "Window.h"
#include "Geometry.h"
#include "Texture.h"
#include "_SDL_System.h"
#include <SDL_render.h>
#include <stdexcept>

static void convertRectangle(const TanTech::Rectangle& src_rect, SDL_Rect& converted_rect) {
		converted_rect.w = src_rect.w;
		converted_rect.h = src_rect.h;
		converted_rect.x = src_rect.x;
		converted_rect.y = src_rect.y;
}

TanTech::Renderer::Renderer(Window& window): _renderer(0) {
	try {
		TanTech::_SDL_System::registerObject(TanTech::_SDL_System::VIDEO);
	}
	catch (std::runtime_error ex) {
		throw ex;
	}
	_renderer = SDL_CreateRenderer(window._window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == 0) {
		TanTech::_SDL_System::unregisterObject(TanTech::_SDL_System::VIDEO);
		throw std::runtime_error(SDL_GetError());
	}
	if (SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}

TanTech::Renderer::~Renderer() {
	SDL_DestroyRenderer(_renderer);
	TanTech::_SDL_System::unregisterObject(TanTech::_SDL_System::VIDEO);
}

void TanTech::Renderer::setBlendMode(BlendMode mode) {
	switch (mode) {
	case NONE:
		if (SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_NONE) != 0) {
			throw std::runtime_error(SDL_GetError());
		}
		break;
	case BLEND:
		if (SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND) != 0) {
			throw std::runtime_error(SDL_GetError());
		}
		break;
	case ADD:
		if (SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_ADD) != 0) {
			throw std::runtime_error(SDL_GetError());
		}
		break;
	case MODULATE:
		if (SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_MOD) != 0) {
			throw std::runtime_error(SDL_GetError());
		}
		break;
	}
}

void TanTech::Renderer::setDrawColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	if (SDL_SetRenderDrawColor(_renderer, r, g, b, a)) {
		throw std::runtime_error(SDL_GetError());
	}
}

void TanTech::Renderer::drawPoint(int x, int y) {
	if (SDL_RenderDrawPoint(_renderer, x, y) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}

void TanTech::Renderer::drawLine(int x1, int y1, int x2, int y2) {
	if (SDL_RenderDrawLine(_renderer, x1, y1, x2, y2) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}

void TanTech::Renderer::drawRect(const Rectangle* rect) {
	SDL_Rect sdl_rect;
	SDL_Rect* rect_ptr = 0;
	if (rect != 0) {
		convertRectangle(*rect, sdl_rect);
		rect_ptr = &sdl_rect;
	}
	if (SDL_RenderDrawRect(_renderer, rect_ptr) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}

void TanTech::Renderer::fillRect(const Rectangle* rect) {
	SDL_Rect sdl_rect;
	SDL_Rect* rect_ptr = 0;
	if (rect != 0) {
		convertRectangle(*rect, sdl_rect);
		rect_ptr = &sdl_rect;
	}
	if (SDL_RenderFillRect(_renderer, rect_ptr) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}

void TanTech::Renderer::clear() {
	if (SDL_RenderClear(_renderer) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}

void TanTech::Renderer::present() {
	SDL_RenderPresent(_renderer);
}

void TanTech::Renderer::setLogicalSize(int w, int h) {
	if (SDL_RenderSetLogicalSize(_renderer, w, h) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}

void TanTech::Renderer::copy(const Texture& texture, const Rectangle* src_rect, const Rectangle* dest_rect) {
	SDL_Rect src, dest;
	SDL_Rect* src_ptr = 0;
	SDL_Rect* dest_ptr = 0;
	if (src_rect != 0) {
		convertRectangle(*src_rect, src);
		src_ptr = &src;
	}
	if (dest_rect != 0) {
		convertRectangle(*dest_rect, dest);
		dest_ptr = &dest;
	}
	if (SDL_RenderCopy(_renderer, texture._texture, src_ptr, dest_ptr) != 0) {
		throw std::runtime_error(SDL_GetError());
	}
}
