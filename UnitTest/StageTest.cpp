#include "pch.h"
#include "ModelDatabase.hpp"
#include "ModelInstance.hpp"
#include "Stage.hpp"
#include "DxLib.h"
#include <stdexcept>

namespace game {
	// draw test in main function
	TEST_CLASS(StageTest)
	{
	public:
		TEST_METHOD(ConstructorWithValidScale) {
			Stage stage(VGet(100, 100, 100),
				"../../Onigokko/ground.txt",
				"../../Onigokko/wall.txt");

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
			try {
				Stage stage(VGet(0, 0, 0),
					"../../Onigokko/ground.txt",
					"../../Onigokko/wall.txt");
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
			try {
				Stage stage(VGet(100, -14, 100),
					"../../Onigokko/ground.txt",
					"../../Onigokko/wall.txt");
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(ConstructorModelDBValidScale_NotLoaded) {
			ModelDatabasePtr mdb(new ModelDatabase());
			Stage stage(mdb, VGet(100, 123, 5),
				"../../Onigokko/ground.txt",
				"../../Onigokko/wall.txt");

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
		TEST_METHOD(ConstructorModelDBValidScale_Loaded) {
			ModelDatabasePtr mdb(new ModelDatabase());
			mdb->load("floor", "../../Onigokko/ground.txt");
			mdb->load("wall", "../../Onigokko/wall.txt");

			Stage stage(mdb, VGet(100, 100, 100),
				"../../Onigokko/ground.txt",
				"../../Onigokko/wall.txt");

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

			Assert::AreEqual(static_cast<ModelResourceRef>(mdb->fetch("floor", "honyarara")), floor->getModelResource());
			Assert::AreEqual(static_cast<ModelResourceRef>(mdb->fetch("wall", "honyarara")), walls[0]->getModelResource());
			Assert::AreEqual(static_cast<ModelResourceRef>(mdb->fetch("wall", "honyarara")), walls[1]->getModelResource());
			Assert::AreEqual(static_cast<ModelResourceRef>(mdb->fetch("wall", "honyarara")), walls[2]->getModelResource());
			Assert::AreEqual(static_cast<ModelResourceRef>(mdb->fetch("wall", "honyarara")), walls[3]->getModelResource());
			Assert::AreEqual(static_cast<ModelResourceRef>(mdb->fetch("floor", "honyarara")), obj[0]->getModelResource());
			Assert::AreEqual(static_cast<ModelResourceRef>(mdb->fetch("wall", "honyarara")), obj[1]->getModelResource());
			Assert::AreEqual(static_cast<ModelResourceRef>(mdb->fetch("wall", "honyarara")), obj[2]->getModelResource());
			Assert::AreEqual(static_cast<ModelResourceRef>(mdb->fetch("wall", "honyarara")), obj[3]->getModelResource());
			Assert::AreEqual(static_cast<ModelResourceRef>(mdb->fetch("wall", "honyarara")), obj[4]->getModelResource());
		}
	};
}
