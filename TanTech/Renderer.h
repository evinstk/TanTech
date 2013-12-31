////////////////////////////////////////////////////////////////////////////////
// TanTech Game Engine
// Copyright (c) 2013 Tanner Evins
// Permission to use, copy, modify, distribute and sell this software for any
//     purpose is hereby granted without fee, provided that the above copyright
//     notice appear in all copies and that both that copyright notice and this
//     permission notice appear in supporting documentation.
// The author makes no representations about the suitability of this software
//     for any purpose. It is provided "as is" without express or implied
//     warranty.
////////////////////////////////////////////////////////////////////////////////
#ifndef RENDERER_H
#define RENDERER_H

struct SDL_Renderer;

namespace TanTech {

class Window;
class Texture;
struct Rectangle;

class Renderer {
public:
	enum BlendMode {
		NONE, BLEND, ADD, MODULATE
	};
	Renderer(Window& window);
	~Renderer();
	void setBlendMode(BlendMode mode);
	void setDrawColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void drawPoint(int x, int y);
	void drawLine(int x1, int y1, int x2, int y2);
	void drawRect(const Rectangle* rect);
	void fillRect(const Rectangle* rect);
	void clear();
	void present();
	void setLogicalSize(int w, int h);
	void copy(const Texture& texture, const Rectangle* src_rect, const Rectangle* dest_rect);
private:
	SDL_Renderer* _renderer;
	friend class Texture;

	// Disabled
	Renderer(const Renderer&);
	Renderer& operator=(const Renderer&);
};

}

#endif
