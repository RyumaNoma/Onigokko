#include "pch.h"
#include "Stage.hpp"
#include "DxLib.h"
#include <stdexcept>

namespace game {
	// draw test in main function
	TEST_CLASS(StageTest)
	{
	public:
		TEST_METHOD(ConstructorWithValidScale) {
			Stage stage(VGet(100, 100, 100));

			auto floor = stage.getFloor();
			auto walls = stage.getWalls();
			auto obj = stage.getAllObjects();

			Assert::IsNotNull(floor.get());
			Assert::AreEqual(4ULL, walls.size());
			Assert::IsNotNull(walls[0].get());
			Assert::IsNotNull(walls[1].get());
			Assert::IsNotNull(walls[2].get());
			Assert::IsNotNull(walls[3].get());
			Assert::AreEqual(5ULL, obj.size());
			Assert::AreEqual(floor.get(), obj[0].get());
			Assert::AreEqual(walls[0].get(), obj[1].get());
			Assert::AreEqual(walls[1].get(), obj[2].get());
			Assert::AreEqual(walls[2].get(), obj[3].get());
			Assert::AreEqual(walls[3].get(), obj[4].get());
		}
		TEST_METHOD(ConstructorWithZeroScale) {
			Stage stage(VGet(100, 0, 200));
			try {
				Stage stage(VGet(100, 100, 100));
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(ConstructorWithMinusScale) {
			Stage stage(VGet(-100, -100, -100));
			try {
				Stage stage(VGet(100, 100, 100));
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
	};
}
