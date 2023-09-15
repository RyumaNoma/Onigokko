#include "Timer.hpp"
#include "Clock.hpp"

namespace game {
	Timer::Timer(ClockRef clock)
		: _clock(clock)
		, _start(0)
	{
		start();
	}

	void Timer::start() {
		_start = _clock->now();
	}

	// Clockクラスの単調増加性を前提としている
	size_t Timer::getElapsed() const {
		return _clock->now() - _start;
	}
}
