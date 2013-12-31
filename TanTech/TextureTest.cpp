#include "Texture.h"
#include "Renderer.h"
#include "Surface.h"
#include "Window.h"
#include "_SDL_System.h"
#include <SDL.h>
#include <boost/test/unit_test.hpp>

//struct TextureFixture {
//	TanTech::Window window;
//	TanTech::Renderer renderer;
//	TanTech::Surface surface;
//	TextureFixture():
//		window("Window", 640, 480),
//		renderer(window),
//		surface("Koala.jpg", window) {
//	}
//};

BOOST_AUTO_TEST_SUITE(TextureSuite)

	BOOST_AUTO_TEST_CASE(TextureConstructorTest) {
		TanTech::Window window("Window", 640, 480);
		TanTech::Renderer renderer(window);
		TanTech::Surface surface("Koala.jpg", window);
		BOOST_CHECK_NO_THROW(TanTech::Texture(renderer, surface));
	}

	BOOST_AUTO_TEST_CASE(TextureResourceTest) {
		{
			BOOST_CHECK_EQUAL(SDL_WasInit(SDL_INIT_VIDEO), 0);
			BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), false);
			TanTech::Window window("Window", 640, 480);
			TanTech::Renderer renderer(window);
			TanTech::Surface surface("Koala.jpg", window);
			TanTech::Texture texture(renderer, surface);
			BOOST_CHECK(SDL_WasInit(SDL_INIT_VIDEO) != 0);
			BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), true);
		}
		BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), false);
	}

BOOST_AUTO_TEST_SUITE_END()
