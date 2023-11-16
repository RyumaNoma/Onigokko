#include "pch.h"
#include "MessageServer.hpp"
#include "Physics.hpp"
#include "MessageClientStub.hpp"
#include "ModelDatabase.hpp"

namespace game {
	TEST_CLASS(PhysicsTest)
	{
	public:
		//TODO: checkCollisionのテスト
		//TODO: モデルの向きのテスト
		TEST_METHOD(NoneCollision) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			std::shared_ptr<Physics> p(new Physics(server, mdb));
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("playerModel");
			stub->raiseHand("playerModel");

			// stage player1 player0
			p->receive("setPlayerNum(2)");
			p->receive("stageAABB(0,0,0,100,100,100)");
			p->receive("playerScale(1, 100)");
			p->receive("playerPosition(1, 200, 0, 0)");
			p->receive("playerScale(0, 100)");
			p->receive("playerPosition(0, 700, 0, 0)");
			p->receive("playerMove(0,-100,0,0)");
			p->receive("check()");

			server->sendAll();
			auto msg = stub->getReceivedMessages();
			Assert::AreEqual(2ULL, msg.size());
			Assert::AreEqual(std::string("move(-100,0,0)"), msg.at(0));
			Assert::AreEqual(std::string("move(0,0,0)"), msg.at(1));

			Assert::IsFalse(p->isCollided(0, 1));
			Assert::IsFalse(p->isCollided(1, 0));
			Assert::IsFalse(p->isCollidedStage(0));
			Assert::IsFalse(p->isCollidedStage(1));
		}
		TEST_METHOD(Collision_Stage) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			std::shared_ptr<Physics> p(new Physics(server, mdb));
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("playerModel");
			stub->raiseHand("playerModel");

			// stage player0 player1
			p->receive("setPlayerNum(2)");
			p->receive("stageAABB(0,0,0,100,100,100)");
			p->receive("playerScale(0, 100)");
			p->receive("playerPosition(0, 200, 0, 0)");
			p->receive("playerScale(1, 100)");
			p->receive("playerPosition(1, 400, 0, 0)");
			p->receive("playerMove(0,-1000,0,0)");
			p->receive("check()");

			server->sendAll();
			auto msg = stub->getReceivedMessages();
			Assert::AreEqual(2ULL, msg.size());
			Assert::AreEqual(std::string("move(-50,0,0)"), msg.at(0));
			Assert::AreEqual(std::string("move(0,0,0)"), msg.at(1));

			Assert::AreEqual(2.0f, p->collidedTime(0, 1));
			Assert::IsFalse(p->isCollided(0, 1));
			Assert::IsFalse(p->isCollided(1, 0));
			Assert::IsTrue(p->isCollidedStage(0));
			Assert::IsFalse(p->isCollidedStage(1));
		}
		TEST_METHOD(Collision_Player) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			std::shared_ptr<Physics> p(new Physics(server, mdb));
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("playerModel");
			stub->raiseHand("playerModel");

			// stage player0 player1
			p->receive("setPlayerNum(2)");
			p->receive("stageAABB(0,0,0,100,100,100)");
			p->receive("playerScale(0, 100)");
			p->receive("playerPosition(0, 200, 0, 0)");
			p->receive("playerScale(1, 100)");
			p->receive("playerPosition(1, 400, 0, 0)");
			p->receive("playerMove(0,1000,0,0)");
			p->receive("check()");

			server->sendAll();
			auto msg = stub->getReceivedMessages();
			Assert::AreEqual(2ULL, msg.size());
			Assert::AreEqual(std::string("move(1000,0,0)"), msg.at(0));
			Assert::AreEqual(std::string("move(0,0,0)"), msg.at(1));

			Assert::IsTrue(p->isCollided(0, 1));
			Assert::IsTrue(p->isCollided(1, 0));
			Assert::IsFalse(p->isCollidedStage(0));
			Assert::IsFalse(p->isCollidedStage(1));
		}
		TEST_METHOD(Collision_StagePlayer) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			std::shared_ptr<Physics> p(new Physics(server, mdb));
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("playerModel");
			stub->raiseHand("playerModel");

			// player0 stage  player1
			p->receive("setPlayerNum(2)");
			p->receive("playerScale(0, 100)");
			p->receive("playerPosition(0, 0, 0, 0)");
			p->receive("stageAABB(200,0,0,300,100,100)");
			p->receive("playerScale(1, 100)");
			p->receive("playerPosition(1, 400, 0, 0)");
			p->receive("playerMove(0,1000,0,0)");
			p->receive("check()");

			server->sendAll();
			auto msg = stub->getReceivedMessages();
			Assert::AreEqual(2ULL, msg.size());
			Assert::AreEqual(std::string("move(100,0,0)"), msg.at(0));
			Assert::AreEqual(std::string("move(0,0,0)"), msg.at(1));

			Assert::IsFalse(p->isCollided(0, 1));
			Assert::IsFalse(p->isCollided(1, 0));
			Assert::IsTrue(p->isCollidedStage(0));
			Assert::IsFalse(p->isCollidedStage(1));
		}
		TEST_METHOD(Collision_PlayerStage) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			std::shared_ptr<Physics> p(new Physics(server, mdb));
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("playerModel");
			stub->raiseHand("playerModel");

			// stage player1 player0
			p->receive("setPlayerNum(2)");
			p->receive("stageAABB(0,0,0,100,100,100)");
			p->receive("playerScale(1, 100)");
			p->receive("playerPosition(1, 200, 0, 0)");
			p->receive("playerScale(0, 100)");
			p->receive("playerPosition(0, 400, 0, 0)");
			p->receive("playerMove(0,-1000,0,0)");
			p->receive("check()");

			server->sendAll();
			auto msg = stub->getReceivedMessages();
			Assert::AreEqual(2ULL, msg.size());
			Assert::AreEqual(std::string("move(-250,0,0)"), msg.at(0));
			Assert::AreEqual(std::string("move(0,0,0)"), msg.at(1));

			Assert::IsTrue(p->isCollided(0, 1));
			Assert::IsTrue(p->isCollided(1, 0));
			Assert::IsTrue(p->isCollidedStage(0));
			Assert::IsFalse(p->isCollidedStage(1));
		}
		TEST_METHOD(Collision_PlayerPlayer) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			std::shared_ptr<Physics> p(new Physics(server, mdb));
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("playerModel");
			stub->raiseHand("playerModel");
			stub->raiseHand("playerModel");

			// player0 player1 player2 stage
			p->receive("setPlayerNum(3)");
			p->receive("playerScale(0, 100)");
			p->receive("playerPosition(0, 0, 0, 0)");
			p->receive("playerScale(1, 100)");
			p->receive("playerPosition(1, 200, 0, 0)");
			p->receive("playerScale(2, 100)");
			p->receive("playerPosition(2, 400, 0, 0)");
			p->receive("stageAABB(600,0,0,700,100,100)");
			p->receive("playerMove(0,400,0,0)");
			p->receive("check()");

			server->sendAll();
			auto msg = stub->getReceivedMessages();
			Assert::AreEqual(3ULL, msg.size());
			Assert::AreEqual(std::string("move(400,0,0)"), msg.at(0));
			Assert::AreEqual(std::string("move(0,0,0)"), msg.at(1));
			Assert::AreEqual(std::string("move(0,0,0)"), msg.at(2));

			Assert::IsTrue(p->isCollided(0, 1));
			Assert::IsTrue(p->isCollided(0, 2));
			Assert::IsTrue(p->isCollided(1, 0));
			Assert::IsFalse(p->isCollided(1, 2));
			Assert::IsTrue(p->isCollided(2, 0));
			Assert::IsFalse(p->isCollided(2, 1));
			Assert::IsFalse(p->isCollidedStage(0));
			Assert::IsFalse(p->isCollidedStage(1));
			Assert::IsFalse(p->isCollidedStage(2));
		}
		TEST_METHOD(Collision_PlayerPlayerStage) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			std::shared_ptr<Physics> p(new Physics(server, mdb));
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("playerModel");
			stub->raiseHand("playerModel");
			stub->raiseHand("playerModel");

			// player0 player1 player2 stage
			p->receive("setPlayerNum(3)");
			p->receive("playerScale(0, 100)");
			p->receive("playerPosition(0, 0, 0, 0)");
			p->receive("playerScale(1, 100)");
			p->receive("playerPosition(1, 200, 0, 0)");
			p->receive("playerScale(2, 100)");
			p->receive("playerPosition(2, 400, 0, 0)");
			p->receive("stageAABB(600,0,0,700,100,100)");
			p->receive("playerMove(0,1000,0,0)");
			p->receive("check()");

			server->sendAll();
			auto msg = stub->getReceivedMessages();
			Assert::AreEqual(3ULL, msg.size());
			Assert::AreEqual(std::string("move(500,0,0)"), msg.at(0));
			Assert::AreEqual(std::string("move(0,0,0)"), msg.at(1));
			Assert::AreEqual(std::string("move(0,0,0)"), msg.at(2));

			Assert::IsTrue(p->isCollided(0, 1));
			Assert::IsTrue(p->isCollided(0, 2));
			Assert::IsTrue(p->isCollided(1, 0));
			Assert::IsFalse(p->isCollided(1, 2));
			Assert::IsTrue(p->isCollided(2, 0));
			Assert::IsFalse(p->isCollided(2, 1));
			Assert::IsTrue(p->isCollidedStage(0));
			Assert::IsFalse(p->isCollidedStage(1));
			Assert::IsFalse(p->isCollidedStage(2));
		}
	};
}
