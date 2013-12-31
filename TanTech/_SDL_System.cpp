#include "_SDL_System.h"
#include <SDL.h>
#include <stdexcept>

bool TanTech::_SDL_System::_initialized(false);
int TanTech::_SDL_System::_init_mask(0);
boost::mutex TanTech::_SDL_System::_mutex;
int TanTech::_SDL_System::_video_objects(0);
int TanTech::_SDL_System::_timer_objects(0);
int TanTech::_SDL_System::_thread_objects(0);

bool TanTech::_SDL_System::isInit() {
	return _initialized;
}

void TanTech::_SDL_System::registerObject(int system_flags) {
	boost::mutex::scoped_lock lock(_mutex);
	if (!_initialized) {
		if (SDL_Init(0) != 0) {
			throw std::runtime_error(SDL_GetError());
		}
		_initialized = true;
	}
	if (_isRequested(system_flags, VIDEO)) {
		if (!_isInitialized(VIDEO)) {
			if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
				throw std::runtime_error(SDL_GetError());
			}
			_init_mask |= VIDEO;
		}
		++_video_objects;
	}
	if (_isRequested(system_flags, TIMER)) {
		if (!_isInitialized(TIMER)) {
			if (SDL_InitSubSystem(SDL_INIT_TIMER) != 0) {
				throw std::runtime_error(SDL_GetError());
			}
			_init_mask |= TIMER;
		}
		++_timer_objects;
	}
	if (_isRequested(system_flags, THREADING)) {
		if (!_isInitialized(THREADING)) {
			// No SDL SubSystem, but still necessary to keep bitmask consistent.
			_init_mask |= THREADING;
		}
		++_thread_objects;
	}
}

void TanTech::_SDL_System::unregisterObject(int system_flags) {
	boost::mutex::scoped_lock lock(_mutex);
	if (!_initialized) return;
	if (_isRequested(system_flags, VIDEO) && _isInitialized(VIDEO)) {
		if (--_video_objects == 0) {
			SDL_QuitSubSystem(SDL_INIT_VIDEO);
			_init_mask ^= VIDEO;
		}
	}
	if (_isRequested(system_flags, TIMER) && _isInitialized(TIMER)) {
		if (--_timer_objects == 0) {
			SDL_QuitSubSystem(SDL_INIT_TIMER);
			_init_mask ^= TIMER;
		}
	}
	if (_isRequested(system_flags, THREADING) && _isInitialized(THREADING)) {
		if (--_thread_objects == 0) {
			_init_mask ^= THREADING;
		}
	}
	if (_init_mask == 0) {
		SDL_Quit();
		_initialized = false;
	}
}

bool TanTech::_SDL_System::_isRequested(int request_flags, SubSystem candidate) {
	return ((request_flags & candidate) != 0);
}

bool TanTech::_SDL_System::_isInitialized(SubSystem candidate) {
	return ((_init_mask & candidate) != 0);
}
