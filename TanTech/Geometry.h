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
#ifndef RECTANGLE_H
#define RECTANGLE_H

namespace TanTech {

	//////////////////////////////////////////////////////////////////////////
	///  \struct Rectangle
	///
	///  Header-only struct for storing width, height, and position data for a
	///  rectangle.
	//////////////////////////////////////////////////////////////////////////
	struct Rectangle {
		unsigned short w;
		unsigned short h;
		short x;
		short y;
		Rectangle(unsigned short w, unsigned short h, short x, short y):
			w(w), h(h), x(x), y(y) {
		}
	};

}

#endif
