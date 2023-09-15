#include "pch.h"
#include "Clock.hpp"

namespace game {
	TEST_CLASS(ClockTest)
	{
	public:
		TEST_METHOD(DefaultConstructor) {
			Clock clock;
			Assert::AreEqual(0ULL, clock.now());
		}
		TEST_METHOD(CountUp) {
			Clock clock;
			clock.countUp();
			Assert::AreEqual(1ULL, clock.now());
			clock.countUp();
			clock.countUp();
			Assert::AreEqual(3ULL, clock.now());
			Assert::AreEqual(3ULL, clock.now());
		}
		TEST_METHOD(CountUp100) {
			Clock clock;
			for (int i = 0; i < 100; ++i) {
				clock.countUp();
			}
			Assert::AreEqual(100ULL, clock.now());
		}
	};
}
