#include "pch.h"
#include "PlayerModel.hpp"
#include "ModelDatabase.hpp"
#include "MessageServer.hpp"
#include "MessageClientStub.hpp"
#include "MessageParser.hpp"
#include <cassert>

namespace game {
	TEST_CLASS(PlayerModelTest)
	{
	public:
		TEST_METHOD(ConstructorWithZeroScale) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			try {
				PlayerModel player(server, mdb, 0, "../../Onigokko/person.txt");
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
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			try {
				PlayerModel player(server, mdb, -10, "../../Onigokko/person.txt");
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(Constructor_NotLoaded) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			PlayerModel player(server, mdb, 100, "../../Onigokko/person.txt");

			Assert::IsNotNull(player.getModelInstance().get());
		}
		TEST_METHOD(Constructor_Loaded) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			mdb->load("person", "../../Onigokko/person.txt");
			PlayerModel player(server, mdb, 100, "../../Onigokko/person.txt");

			Assert::IsNotNull(player.getModelInstance().get());
		}
		TEST_METHOD(AABB) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			std::shared_ptr<PlayerModel> player(new PlayerModel(server, mdb, 100, "../../Onigokko/person.txt"));
			player->raiseHand("Player");
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("Physics");

			player->receive("getAABB()");
			server->sendAll();

			auto&& messages = stub->getReceivedMessages();
			Assert::AreEqual(1ULL, messages.size());
			Assert::AreEqual(
				std::string("playerAABB(0,-50,0,0,100,100,100)"),
				messages.at(0)
			);
		}
		TEST_METHOD(NotSetSpeed) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			PlayerModel player(server, mdb, 100, "../../Onigokko/person.txt");

			Assert::AreEqual(0.0f, player.getSpeed());
		}
		TEST_METHOD(SetSpeed) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			PlayerModel player(server, mdb, 100, "../../Onigokko/person.txt");

			player.receive("setSpeed(100.0)");

			Assert::AreEqual(100.0f, player.getSpeed());
		}
		TEST_METHOD(MoveLeft) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			std::shared_ptr<PlayerModel> player(new PlayerModel(server, mdb, 100, "../../Onigokko/person.txt"));
			player->raiseHand("Player");
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("Physics");

			player->receive("setSpeed(100.0)");
			player->receive("move(LEFT)");
			server->sendAll();

			auto&& messages = stub->getReceivedMessages();
			Assert::AreEqual(2ULL, messages.size());
			Assert::AreEqual(
				std::string("playerMove(0,-100,0,0)"),
				messages.at(0)
			);
			Assert::AreEqual(
				std::string("playerFace(0,-100,0,0)"),
				messages.at(1)
			);
		}
		TEST_METHOD(MoveRight) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			std::shared_ptr<PlayerModel> player(new PlayerModel(server, mdb, 100, "../../Onigokko/person.txt"));
			player->raiseHand("Player");
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("Physics");

			player->receive("setSpeed(100.0)");
			player->receive("move(RIGHT)");
			server->sendAll();

			auto&& messages = stub->getReceivedMessages();
			Assert::AreEqual(2ULL, messages.size());
			Assert::AreEqual(
				std::string("playerMove(0,100,0,0)"),
				messages.at(0)
			);
			Assert::AreEqual(
				std::string("playerFace(0,100,0,0)"),
				messages.at(1)
			);
		}
		TEST_METHOD(MoveUp) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			std::shared_ptr<PlayerModel> player(new PlayerModel(server, mdb, 100, "../../Onigokko/person.txt"));
			player->raiseHand("Player");
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("Physics");

			player->receive("setSpeed(100.0)");
			player->receive("move(UP)");
			server->sendAll();

			auto&& messages = stub->getReceivedMessages();
			Assert::AreEqual(2ULL, messages.size());
			Assert::AreEqual(
				std::string("playerMove(0,0,0,100)"),
				messages.at(0)
			);
			Assert::AreEqual(
				std::string("playerFace(0,0,0,100)"),
				messages.at(1)
			);
		}
		TEST_METHOD(MoveDown) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			std::shared_ptr<PlayerModel> player(new PlayerModel(server, mdb, 100, "../../Onigokko/person.txt"));
			player->raiseHand("Player");
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("Physics");

			player->receive("setSpeed(100.0)");
			player->receive("move(DOWN)");
			server->sendAll();

			auto&& messages = stub->getReceivedMessages();
			Assert::AreEqual(2ULL, messages.size());
			Assert::AreEqual(
				std::string("playerMove(0,0,0,-100)"),
				messages.at(0)
			);
			Assert::AreEqual(
				std::string("playerFace(0,0,0,-100)"),
				messages.at(1)
			);
		}
		TEST_METHOD(MoveLeftUp) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			std::shared_ptr<PlayerModel> player(new PlayerModel(server, mdb, 100, "../../Onigokko/person.txt"));
			player->raiseHand("Player");
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("Physics");

			player->receive("setSpeed(100.0)");
			player->receive("move(LEFT_UP)");
			server->sendAll();

			auto&& messages = stub->getReceivedMessages();
			Assert::AreEqual(2ULL, messages.size());

			MessageParser mp0(messages.at(0));
			Assert::AreEqual(std::string("playerMove"), mp0.getSignature());
			Assert::AreEqual(0, mp0.getArgumentAsInteger(0));
			assert(-70.72 <= mp0.getArgumentAsDouble(1) && mp0.getArgumentAsDouble(1) <= -70.71);
			Assert::AreEqual(0.0, mp0.getArgumentAsDouble(2));
			assert(70.71 <= mp0.getArgumentAsDouble(3) && mp0.getArgumentAsDouble(3) <= 70.72);

			MessageParser mp1(messages.at(1));
			Assert::AreEqual(std::string("playerFace"), mp1.getSignature());
			Assert::AreEqual(0, mp1.getArgumentAsInteger(0));
			assert(-70.72 <= mp1.getArgumentAsDouble(1) && mp1.getArgumentAsDouble(1) <= -70.71);
			Assert::AreEqual(0.0, mp1.getArgumentAsDouble(2));
			assert(70.71 <= mp1.getArgumentAsDouble(3) && mp1.getArgumentAsDouble(3) <= 70.72);
		}
		TEST_METHOD(MoveLeftDown) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			std::shared_ptr<PlayerModel> player(new PlayerModel(server, mdb, 100, "../../Onigokko/person.txt"));
			player->raiseHand("Player");
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("Physics");

			player->receive("setSpeed(100.0)");
			player->receive("move(LEFT_DOWN)");
			server->sendAll();

			auto&& messages = stub->getReceivedMessages();
			Assert::AreEqual(2ULL, messages.size());

			MessageParser mp0(messages.at(0));
			Assert::AreEqual(std::string("playerMove"), mp0.getSignature());
			Assert::AreEqual(0, mp0.getArgumentAsInteger(0));
			assert(-70.72 <= mp0.getArgumentAsDouble(1) && mp0.getArgumentAsDouble(1) <= -70.71);
			Assert::AreEqual(0.0, mp0.getArgumentAsDouble(2));
			assert(-70.72 <= mp0.getArgumentAsDouble(3) && mp0.getArgumentAsDouble(3) <= -70.71);

			MessageParser mp1(messages.at(1));
			Assert::AreEqual(std::string("playerFace"), mp1.getSignature());
			Assert::AreEqual(0, mp1.getArgumentAsInteger(0));
			assert(-70.72 <= mp1.getArgumentAsDouble(1) && mp1.getArgumentAsDouble(1) <= -70.71);
			Assert::AreEqual(0.0, mp1.getArgumentAsDouble(2));
			assert(-70.72 <= mp1.getArgumentAsDouble(3) && mp1.getArgumentAsDouble(3) <= -70.71);
		}
		TEST_METHOD(MoveRightUp) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			std::shared_ptr<PlayerModel> player(new PlayerModel(server, mdb, 100, "../../Onigokko/person.txt"));
			player->raiseHand("Player");
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("Physics");

			player->receive("setSpeed(100.0)");
			player->receive("move(RIGHT_UP)");
			server->sendAll();

			auto&& messages = stub->getReceivedMessages();
			Assert::AreEqual(2ULL, messages.size());

			MessageParser mp0(messages.at(0));
			Assert::AreEqual(std::string("playerMove"), mp0.getSignature());
			Assert::AreEqual(0, mp0.getArgumentAsInteger(0));
			assert(70.71 <= mp0.getArgumentAsDouble(1) && mp0.getArgumentAsDouble(1) <= 70.72);
			Assert::AreEqual(0.0, mp0.getArgumentAsDouble(2));
			assert(70.71 <= mp0.getArgumentAsDouble(3) && mp0.getArgumentAsDouble(3) <= 70.72);

			MessageParser mp1(messages.at(1));
			Assert::AreEqual(std::string("playerFace"), mp1.getSignature());
			Assert::AreEqual(0, mp1.getArgumentAsInteger(0));
			assert(70.71 <= mp1.getArgumentAsDouble(1) && mp1.getArgumentAsDouble(1) <= 70.72);
			Assert::AreEqual(0.0, mp1.getArgumentAsDouble(2));
			assert(70.71 <= mp1.getArgumentAsDouble(3) && mp1.getArgumentAsDouble(3) <= 70.72);
		}
		TEST_METHOD(MoveRightDown) {
			MessageServerPtr server(new MessageServer());
			ModelDatabasePtr mdb(new ModelDatabase());
			std::shared_ptr<PlayerModel> player(new PlayerModel(server, mdb, 100, "../../Onigokko/person.txt"));
			player->raiseHand("Player");
			std::shared_ptr<MessageClientStub1> stub(new MessageClientStub1(server));
			stub->raiseHand("Physics");

			player->receive("setSpeed(100.0)");
			player->receive("move(RIGHT_DOWN)");
			server->sendAll();

			auto&& messages = stub->getReceivedMessages();
			Assert::AreEqual(2ULL, messages.size());

			MessageParser mp0(messages.at(0));
			Assert::AreEqual(std::string("playerMove"), mp0.getSignature());
			Assert::AreEqual(0, mp0.getArgumentAsInteger(0));
			assert(70.71 <= mp0.getArgumentAsDouble(1) && mp0.getArgumentAsDouble(1) <= 70.72);
			Assert::AreEqual(0.0, mp0.getArgumentAsDouble(2));
			assert(-70.72 <= mp0.getArgumentAsDouble(3) && mp0.getArgumentAsDouble(3) <= -70.71);

			MessageParser mp1(messages.at(1));
			Assert::AreEqual(std::string("playerFace"), mp1.getSignature());
			Assert::AreEqual(0, mp1.getArgumentAsInteger(0));
			assert(70.71 <= mp1.getArgumentAsDouble(1) && mp1.getArgumentAsDouble(1) <= 70.72);
			Assert::AreEqual(0.0, mp1.getArgumentAsDouble(2));
			assert(-70.72 <= mp1.getArgumentAsDouble(3) && mp1.getArgumentAsDouble(3) <= -70.71);
		}
	};
}
