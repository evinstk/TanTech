#include "Renderer.h"
#include "Window.h"
#include "Surface.h"
#include "Texture.h"
#include "Geometry.h"
#include "_SDL_System.h"
#include <SDL.h>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(RendererTestSuite)

	BOOST_AUTO_TEST_CASE(RendererConstructorTest) {
		TanTech::Window w("Window for Renderer", 640, 480);
		BOOST_CHECK_NO_THROW(TanTech::Renderer r(w));
	}

	BOOST_AUTO_TEST_CASE(RendererResourcesTest) {
		{
			BOOST_CHECK_EQUAL(SDL_WasInit(SDL_INIT_VIDEO), 0);
			BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), false);
			TanTech::Window w("Window for Renderer", 640, 480);
			TanTech::Renderer r(w);
			BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), true);
			BOOST_CHECK(SDL_WasInit(SDL_INIT_VIDEO) != 0);
		}
		BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), false);
	}

	BOOST_AUTO_TEST_CASE(MethodTest) {
		{
			TanTech::Window w("Window for Renderer", 640, 480);
			TanTech::Renderer r(w);
			TanTech::Surface s("Koala.jpg", w);
			TanTech::Texture t(r, s);
			TanTech::Rectangle rect(5,5,40,40);
			r.setLogicalSize(100,100);
			r.setBlendMode(TanTech::Renderer::ADD);
			r.setDrawColor(10, 10, 10, 10);
			r.drawPoint(1,2);
			r.drawLine(3,4,50,60);
			r.fillRect(&rect);
			r.clear();
			r.copy(t, 0, 0);
			r.copy(t, &rect, &rect);
			r.present();
		}
		BOOST_CHECK_EQUAL(TanTech::_SDL_System::isInit(), false);
	}

	//BOOST_AUTO_TEST_SUITE(RendererExceptionSuite)

	//	BOOST_AUTO_TEST_CASE(SizeException) {
	//		TanTech::Renderer* r;
	//		{
	//			TanTech::Window w("Window Out of Scope", 640, 480);
	//			r = new TanTech::Renderer(w);
	//		}
	//		BOOST_CHECK_THROW(r->present(), std::runtime_error);
	//		delete r;
	//	}

	//BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
