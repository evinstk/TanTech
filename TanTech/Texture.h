#ifndef TEXTURE_H
#define TEXTURE_H

struct SDL_Texture;

namespace TanTech {

class Renderer;
class Surface;

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
