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
#ifndef WINDOW_H
#define WINDOW_H

struct SDL_Window;

namespace TanTech {

	//////////////////////////////////////////////////////////////////////////
	///  \class Window
	///
	///  A single window. Pass Window reference to Renderer to set as rendering
	///  context. Constructor without dimensions creates full screen Window.
	//////////////////////////////////////////////////////////////////////////
	class Window {
	public:
		Window(const char* title, int w, int h);
		Window(const char* title);
		~Window();
	private:
		SDL_Window* _window;
		friend class Renderer;
		friend class Surface;

		Window(const Window&);
		Window& operator=(const Window&);
	};

}

#endif
