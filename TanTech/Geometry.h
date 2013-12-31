#ifndef RECTANGLE_H
#define RECTANGLE_H

namespace TanTech {

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
