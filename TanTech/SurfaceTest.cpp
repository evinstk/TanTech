#include "Surface.h"
#include "Window.h"
#include "_SDL_System.h"
#include <SDL.h>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(SurfaceTestSuite)

	BOOST_AUTO_TEST_CASE(SurfaceConstructorTest) {
		TanTech::Window window("Window", 640, 480);
		BOOST_CHECK_NO_THROW(TanTech::Surface("Koala.jpg", window));
	}

	BOOST_AUTO_TEST_CASE(SurfaceResourceTest) {
		{
			BOOST_CHECK_EQUAL(SDL_WasInit(SDL_INIT_VIDEO), 0);
			BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), false);
			TanTech::Window window("Window", 640, 480);
			TanTech::Surface surface("Koala.jpg", window);
			BOOST_CHECK(SDL_WasInit(SDL_INIT_VIDEO) != 0);
			BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), true);
		}
		BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), false);
	}

BOOST_AUTO_TEST_SUITE_END()
