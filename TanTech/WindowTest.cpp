#include "Window.h"
#include "_SDL_System.h"
#include <SDL.h>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(WindowTestSuite)

	BOOST_AUTO_TEST_CASE(WindowConstructorTest) {
		BOOST_CHECK_NO_THROW(TanTech::Window w0("Windowed", 640, 480));
		BOOST_CHECK_NO_THROW(TanTech::Window w1("Full Screen"));
	}

	BOOST_AUTO_TEST_CASE(ResourceWindowTest) {
		{
			BOOST_CHECK_EQUAL(SDL_WasInit(SDL_INIT_VIDEO), 0);
			BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), false);
			TanTech::Window w("Test Window", 640, 480);
			BOOST_CHECK(SDL_WasInit(SDL_INIT_VIDEO) != 0);
			BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), true);
		}
		BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), false);
	}

	BOOST_AUTO_TEST_CASE(MultipleWindowTest) {
		{
			TanTech::Window w0("Test Window", 640, 480);
			{
				TanTech::Window w1("Test Window", 640, 480);
			}
			BOOST_CHECK(SDL_WasInit(SDL_INIT_VIDEO) != 0);
			BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), true);
		}
		BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), false);
	}

BOOST_AUTO_TEST_SUITE_END()
