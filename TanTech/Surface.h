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
#ifndef SURFACE_H
#define SURFACE_H

struct SDL_Surface;

namespace TanTech {

	// Forward declaration of Window dependency.
	class Window;

	///////////////////////////////////////////////////
	///  \class Surface
	///
	///  Loads image file. Passed to Texture to convert
	///  into efficient, driver-specific data.
	///////////////////////////////////////////////////
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
