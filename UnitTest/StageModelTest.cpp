#include "pch.h"
#include "ModelDatabase.hpp"
#include "ModelInstance.hpp"
#include "StageModel.hpp"
#include "MessageServer.hpp"
#include "DxLib.h"
#include "MessageClientStub.hpp"
#include <stdexcept>

namespace game {
	// draw test in main function
	TEST_CLASS(StageModelTest)
	{
	public:
		TEST_METHOD(ConstructorWithValidScale) {
			MessageServerPtr server(new MessageServer());
			StageModel stage(server, VGet(100, 100, 100),
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
				MessageServerPtr server(new MessageServer());
				StageModel stage(server, VGet(0, 0, 0),
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
				MessageServerPtr server(new MessageServer());
				StageModel stage(server, VGet(100, -14, 100),
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
			MessageServerPtr server(new MessageServer());
			StageModel stage(server, mdb, VGet(100, 123, 5),
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

			MessageServerPtr server(new MessageServer());
			StageModel stage(server, mdb, VGet(100, 100, 100),
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
		TEST_METHOD(AABB) {
			MessageServerPtr server(new MessageServer());
			StageModel stage(server, VGet(100, 200, 300),
				"../../Onigokko/ground.txt",
				"../../Onigokko/wall.txt");
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("Physics");

			stage.receive("getAABB()");
			server->sendAll();

			auto&& messages = stub->getReceivedMessages();
			Assert::AreEqual(
				std::string("stageAABB(0,0,0,100,1,300)"),
				messages.at(0));
			Assert::AreEqual(
				std::string("stageAABB(0,0,-1,101,201,0)"),
				messages.at(1));
			Assert::AreEqual(
				std::string("stageAABB(-1,0,300,100,201,301)"),
				messages.at(2));
			Assert::AreEqual(
				std::string("stageAABB(-1,0,-1,0,201,300)"),
				messages.at(3));
			Assert::AreEqual(
				std::string("stageAABB(100,0,0,101,201,301)"),
				messages.at(4));
		}
	};
}
