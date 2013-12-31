#include "_SDL_System.h"
#include <SDL.h>
#include <boost/test/unit_test.hpp>

struct SubSystems {
	static const int SIZE = 3;
	TanTech::_SDL_System::SubSystem systems[SIZE];
	Uint32 SDL_systems[SIZE - 1];
	SubSystems() {
		systems[0] = TanTech::_SDL_System::VIDEO;
		systems[1] = TanTech::_SDL_System::TIMER;
		systems[2] = TanTech::_SDL_System::THREADING;
		SDL_systems[0] = SDL_INIT_VIDEO;
		SDL_systems[1] = SDL_INIT_TIMER;
	}
};

BOOST_FIXTURE_TEST_SUITE(SDL_SystemsSuite, SubSystems)

	BOOST_AUTO_TEST_CASE(StandardUseTest) {
		BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), false);

		// Outer loop for multiple registration.
		for (int outer = 0; outer < 2; ++outer) {
			for (int i = 0; i < SIZE; ++i) {
				BOOST_CHECK_NO_THROW(TanTech::_SDL_System::registerObject(systems[i]));
				if (systems[i] != TanTech::_SDL_System::THREADING) {
					BOOST_CHECK(SDL_WasInit(SDL_systems[i]) != 0);
				}
				BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), true);
			}
		}

		for (int outer = 0; outer < 2; ++outer) {
			for (int i = 0; i < (SIZE - 1); ++i) {
				BOOST_CHECK_NO_THROW(TanTech::_SDL_System::unregisterObject(systems[i]));
				if (systems[i] != TanTech::_SDL_System::THREADING) {
					if (outer == 0) {
						BOOST_CHECK(SDL_WasInit(SDL_systems[i]) != 0);
					}
					if (outer == 1) {
						BOOST_CHECK_EQUAL(SDL_WasInit(SDL_systems[i]), 0);
					}
				}
				BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), true);
			}
		}
		BOOST_CHECK_NO_THROW(TanTech::_SDL_System::unregisterObject(systems[SIZE - 1]));
		BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), true);
		BOOST_CHECK_NO_THROW(TanTech::_SDL_System::unregisterObject(systems[SIZE - 1]));
		//if (systems[SIZE - 1] != TanTech::_SDL_System::THREADING) {
		//	BOOST_CHECK_EQUAL(SDL_WasInit(SDL_systems[SIZE - 1]), 0);
		//}
		BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), false);
	}

	BOOST_AUTO_TEST_CASE(MaskingTest) {
		BOOST_CHECK_NO_THROW(TanTech::_SDL_System::registerObject(systems[0]|systems[1]|
			systems[2]));
		BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), true);
		BOOST_CHECK(SDL_WasInit(SDL_INIT_VIDEO) != 0);
		BOOST_CHECK(SDL_WasInit(SDL_INIT_TIMER) != 0);
		BOOST_CHECK_NO_THROW(TanTech::_SDL_System::unregisterObject(systems[0]|systems[1]|
			systems[2]));
		//BOOST_CHECK_EQUAL(SDL_WasInit(SDL_INIT_VIDEO), 0);
		//BOOST_CHECK_EQUAL(SDL_WasInit(SDL_INIT_TIMER), 0);
		BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), false);
	}

BOOST_AUTO_TEST_SUITE_END()
