#include "pch.h"
#include "Direction.hpp"

namespace game {
	TEST_CLASS(DirectionTest)
	{
	public:
		TEST_METHOD(DefaultConstructor) {
			Direction dir;
			Assert::AreEqual(0, dir.x());
			Assert::AreEqual(0, dir.y());
		}
		TEST_METHOD(Constructor) {
			Direction dir(3, -4);

			Assert::AreEqual(3, dir.x());
			Assert::AreEqual(-4, dir.y());
		}
		TEST_METHOD(NoneDirection) {
			Direction dir(0, 0);

			Assert::AreEqual(std::string("NONE"), static_cast<std::string>(dir));
		}
		TEST_METHOD(Left) {
			Direction dir(-1, 0);

			Assert::AreEqual(std::string("LEFT"), static_cast<std::string>(dir));
		}
		TEST_METHOD(LeftDown) {
			Direction dir(-10, -10);

			Assert::AreEqual(std::string("LEFT_DOWN"), static_cast<std::string>(dir));
		}
		TEST_METHOD(LeftUp) {
			Direction dir(-10, 10);

			Assert::AreEqual(std::string("LEFT_UP"), static_cast<std::string>(dir));
		}
		TEST_METHOD(Right) {
			Direction dir(1, 0);

			Assert::AreEqual(std::string("RIGHT"), static_cast<std::string>(dir));
		}
		TEST_METHOD(RightDown) {
			Direction dir(10, -10);

			Assert::AreEqual(std::string("RIGHT_DOWN"), static_cast<std::string>(dir));
		}
		TEST_METHOD(RightUp) {
			Direction dir(10, 10);

			Assert::AreEqual(std::string("RIGHT_UP"), static_cast<std::string>(dir));
		}
		TEST_METHOD(Down) {
			Direction dir(-1, -1000);

			Assert::AreEqual(std::string("DOWN"), static_cast<std::string>(dir));
		}
		TEST_METHOD(Up) {
			Direction dir(-1, 1000);

			Assert::AreEqual(std::string("UP"), static_cast<std::string>(dir));
		}
	};
}
