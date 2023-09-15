#include "pch.h"
#include "Clock.hpp"
#include "Timer.hpp"

namespace game {
	TEST_CLASS(TimerTest)
	{
	public:
		TEST_METHOD(Constructor) {
			ClockPtr clock(new Clock());
			Timer tm(clock);

			Assert::AreEqual(0ULL, tm.getElapsed());
		}
		TEST_METHOD(ElapsedZero) {
			ClockPtr clock(new Clock());
			Timer tm(clock);
			tm.start();

			Assert::AreEqual(0ULL, tm.getElapsed());
		}
		TEST_METHOD(ElapsedOne) {
			ClockPtr clock(new Clock());
			Timer tm(clock);

			clock->countUp();

			Assert::AreEqual(1ULL, tm.getElapsed());
		}
		TEST_METHOD(ElapsedMany) {
			ClockPtr clock(new Clock());
			Timer tm(clock);

			clock->countUp();
			clock->countUp();
			clock->countUp();
			clock->countUp();
			clock->countUp();

			Assert::AreEqual(5ULL, tm.getElapsed());
		}
		TEST_METHOD(Restart) {
			ClockPtr clock(new Clock());
			Timer tm(clock);

			clock->countUp();
			clock->countUp();
			clock->countUp();
			Assert::AreEqual(3ULL, tm.getElapsed());

			tm.start();
			Assert::AreEqual(0ULL, tm.getElapsed());

			clock->countUp();
			clock->countUp();
			clock->countUp();
			clock->countUp();
			Assert::AreEqual(4ULL, tm.getElapsed());
		}
	};
}
