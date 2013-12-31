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
#ifndef _SDL_SYSTEM_H
#define _SDL_SYSTEM_H

#include "boost/thread.hpp"

namespace TanTech {

	//////////////////////////////////////////////////////////////////////////////////////
	///  \class _SDL_System
	///
	///  Encapsulates SDL initialization and destruction functions. Ensures that multiple
	///  calls to SDL initialization functions are not made, even if there are multiple
	///  calls to _SDL. This class acts as a buffer between the wrappers that depend on
	///  SDL and the SDL system itself.
	///  Objects that depend on SDL SubSystems register themselves with this class in
	///  construction and unregister in destruction. _SDL_System keeps a count of how many
	///  objects are currently depending on SubSystems; however, it is the responsibility
	///  of the dependent object to remember the SubSystems.
	///  Since the point of the wrappers is to abstract away SDL altogether, this class
	///  should not be used by anything other than the SDL wrappers.
	///  Does not implement RAII; however, clients of the wrappers should have the benefits
	///  of RAII. Provided that the wrappers are properly implemented, memory leakage
	///  should not be a problem.
	//////////////////////////////////////////////////////////////////////////////////////
	class _SDL_System {
	public:
		enum SubSystem {
			VIDEO = 0x01,
			TIMER = 0x02,
			THREADING = 0x04
		};

		static bool isInit();
		static void registerObject(int system_flags);
		static void unregisterObject(int system_flags);
	private:
		static bool _initialized;
		static int _init_mask;
		static int _video_objects;
		static int _timer_objects;
		static int _thread_objects;
		static boost::mutex _mutex;

		static bool _isRequested(int request_flags, SubSystem candidate);
		static bool _isInitialized(SubSystem candidate);
	};

}

#endif
