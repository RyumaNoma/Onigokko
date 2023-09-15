#include "Clock.hpp"

namespace game {
    Clock::Clock()
        : _now(0)
    {}

    void Clock::countUp() {
        ++_now;
    }
}
