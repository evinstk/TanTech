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
#ifndef TEXTURE_H
#define TEXTURE_H

struct SDL_Texture;

namespace TanTech {

	// Forward declaration of dependencies.
	class Renderer;
	class Surface;

	//////////////////////////////////////////////////////////
	///  \class Texture
	///
	///  Holds efficient, driver-representation of pixel data.
	///  Used by Renderer.
	//////////////////////////////////////////////////////////
	class Texture {
	public:
		Texture(const Renderer&, const Surface&);
		~Texture();
	private:
		SDL_Texture* _texture;
		friend class Renderer;

		Texture(const Texture&);
		Texture& operator=(const Texture&);
	};

}

#endif
