#include "pch.h"
#include "MessageServer.hpp"
#include "MessageClientStub.hpp"

namespace game {
	TEST_CLASS(MessageServerTest) {
	public:
		TEST_METHOD(DefaultConstructor) {
			MessageServer mm;

			Assert::IsTrue(mm.getMessages().empty());
			Assert::IsTrue(mm.getCommunicators().empty());
		}

		TEST_METHOD(setValidCommunicator) {
			MessageServerPtr mm(new MessageServer());
			MessageClientPtr enemy(new MessageClientStub1(mm));
			MessageClientPtr gameObj(new MessageClientStub2(mm));

			enemy->raiseHand("enemy");
			gameObj->raiseHand("gameObj");

			Assert::AreEqual(enemy, mm->getCommunicator("enemy", 0));
			Assert::AreEqual(std::string("enemy"), enemy->getTag());
			Assert::AreEqual(0, enemy->getId());
			Assert::AreEqual(gameObj, mm->getCommunicator("gameObj", 0));
			Assert::AreEqual(std::string("gameObj"), gameObj->getTag());
			Assert::AreEqual(0, gameObj->getId());
		};

		TEST_METHOD(setNullCommunicator) {
			MessageServerPtr mm(new MessageServer());
			MessageClientPtr enemy(nullptr);

			try {
				mm->setCommunicator("enemy", enemy);
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}

		TEST_METHOD(getNotexistCommunicator) {
			MessageServerPtr mm(new MessageServer());
			MessageClientPtr enemy(new MessageClientStub1(mm));
			MessageClientPtr gameObj(new MessageClientStub2(mm));

			enemy->raiseHand("enemy");

			Assert::AreEqual(enemy, mm->getCommunicator("enemy", 0));
			Assert::AreEqual(MessageClientPtr(nullptr), mm->getCommunicator("enemy", 2));
			Assert::AreEqual(MessageClientPtr(nullptr), mm->getCommunicator("enemy", -1));
			Assert::AreEqual(MessageClientPtr(nullptr), mm->getCommunicator("enemy", -1));
			Assert::AreEqual(MessageClientPtr(nullptr), mm->getCommunicator("gameObj", 1));
		}

		TEST_METHOD(eraseValidCommunicator) {
			MessageServerPtr mm(new MessageServer());
			std::shared_ptr<MessageClientStub1> enemy(new MessageClientStub1(mm));
			enemy->raiseHand("enemy");
			mm->eraseCommunicator("enemy", 0);
			Assert::AreEqual(MessageClientPtr(nullptr), mm->getCommunicator("enemy", 0));
		}

		TEST_METHOD(eraseNotExistTagCommunicator) {
			MessageServerPtr mm(new MessageServer());
			std::shared_ptr<MessageClientStub1> enemy(new MessageClientStub1(mm));
			enemy->raiseHand("enemy");
			mm->eraseCommunicator("you", 0);
			Assert::AreEqual(MessageClientPtr(enemy), mm->getCommunicator("enemy", 0));
			Assert::AreEqual(MessageClientPtr(nullptr), mm->getCommunicator("you", 0));
		}

		TEST_METHOD(eraseNotExistIdCommunicator) {
			MessageServerPtr mm(new MessageServer());
			std::shared_ptr<MessageClientStub1> enemy(new MessageClientStub1(mm));
			enemy->raiseHand("enemy");
			mm->eraseCommunicator("enemy", 12);
			Assert::AreEqual(MessageClientPtr(enemy), mm->getCommunicator("enemy", 0));
			Assert::AreEqual(MessageClientPtr(nullptr), mm->getCommunicator("enemy", 12));
		}

		TEST_METHOD(eraseCommunicatorTwice) {
			MessageServerPtr mm(new MessageServer());
			std::shared_ptr<MessageClientStub1> enemy(new MessageClientStub1(mm));
			enemy->raiseHand("enemy");
			mm->eraseCommunicator("enemy", 0);
			mm->eraseCommunicator("enemy", 0);
			Assert::AreEqual(MessageClientPtr(nullptr), mm->getCommunicator("enemy", 0));
		}

		TEST_METHOD(ReceiveValidMessage) {
			MessageServerPtr mm(new MessageServer());
			mm->receive("[enemy][1]die()");
		}

		TEST_METHOD(ReceiveInvalidMessage) {
			MessageServerPtr mm(new MessageServer());
			mm->receive("[e)");
			mm->receive("");
		}

		TEST_METHOD(SendAllMultipleMessages) {
			MessageServerPtr mm(new MessageServer());
			std::shared_ptr<MessageClientStub1> enemy(new MessageClientStub1(mm));
			const std::string msg1 = "die()";
			const std::string msg2 = "jump(11)";
			enemy->raiseHand("enemy");
			mm->receive("[enemy][0]" + msg1);
			mm->receive("[enemy][0]" + msg2);
			mm->sendAll();

			Assert::AreEqual(static_cast<size_t>(2), enemy->getReceivedMessages().size());
			Assert::AreEqual(msg1, enemy->getReceivedMessage(0));
			Assert::AreEqual(msg2, enemy->getReceivedMessage(1));
		}
		
		TEST_METHOD(SendAllInvalidMessages) {
			MessageServerPtr mm(new MessageServer());
			std::shared_ptr<MessageClientStub1> enemy(new MessageClientStub1(mm));
			enemy->raiseHand("enemy");
			mm->receive("[e)");
			mm->receive("");
			try {
				mm->sendAll();
			}
			catch (std::runtime_error) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		
		TEST_METHOD(SendAllMessagesBroadcast) {
			MessageServerPtr mm(new MessageServer());
			std::shared_ptr<MessageClientStub1> enemy(new MessageClientStub1(mm));
			const std::string msg = "run(34.5)";
			enemy->raiseHand("enemy");
			enemy->raiseHand("enemy");
			mm->receive("[enemy][Broadcast]" + msg);
			mm->sendAll();


			Assert::AreEqual(std::string("enemy"), enemy->getTag());
			Assert::AreEqual(1, enemy->getId());
			Assert::AreEqual(static_cast<size_t>(2), enemy->getReceivedMessages().size());
			Assert::AreEqual(msg, enemy->getReceivedMessage(0));
			Assert::AreEqual(msg, enemy->getReceivedMessage(1));
		}
		
		TEST_METHOD(SendAllMessageToNotExistTag) {
			MessageServerPtr mm(new MessageServer());
			std::shared_ptr<MessageClientStub1> enemy(new MessageClientStub1(mm));
			enemy->raiseHand("enemy");
			mm->receive("[you][1]run(34.5)");
			mm->sendAll();

			Assert::IsTrue(enemy->getReceivedMessages().empty());
		}
		
		TEST_METHOD(SendAllMessageToNotExistTagBroadcast) {
			MessageServerPtr mm(new MessageServer());
			std::shared_ptr<MessageClientStub1> enemy(new MessageClientStub1(mm));
			enemy->raiseHand("enemy");
			mm->receive("[you][Broadcast]run(34.5)");
			mm->sendAll();

			Assert::IsTrue(enemy->getReceivedMessages().empty());
		}
		
		TEST_METHOD(SendAllMessageToNotExistCommunicator) {
			MessageServerPtr mm(new MessageServer());
			std::shared_ptr<MessageClientStub1> enemy(new MessageClientStub1(mm));
			enemy->raiseHand("enemy");
			mm->receive("[enemy][1]run(34.5)");
			mm->sendAll();

			Assert::IsTrue(enemy->getReceivedMessages().empty());
		}
		
		TEST_METHOD(SendAll0Messages) {
			MessageServerPtr mm(new MessageServer());
			std::shared_ptr<MessageClientStub1> enemy(new MessageClientStub1(mm));
			enemy->raiseHand("enemy");
			mm->sendAll();
		}

		TEST_METHOD(SendMessage) {
			MessageServerPtr mm(new MessageServer());
			std::shared_ptr<MessageClientStub1> enemy(new MessageClientStub1(mm));
			enemy->raiseHand("enemy");

			mm->receive("[enemy][0]run(34.5)");
			mm->send();
			Assert::AreEqual(static_cast<size_t>(1), enemy->getReceivedMessages().size());
			Assert::AreEqual(std::string("run(34.5)"), enemy->getReceivedMessages()[0]);
		}

		TEST_METHOD(SendMultipleMessage) {
			MessageServerPtr mm(new MessageServer());
			std::shared_ptr<MessageClientStub1> enemy(new MessageClientStub1(mm));
			enemy->raiseHand("enemy");

			mm->receive("[enemy][0]run(34.5)");
			mm->receive("[enemy][0]jump()");
			mm->send();
			Assert::AreEqual(static_cast<size_t>(1), enemy->getReceivedMessages().size());
			Assert::AreEqual(std::string("run(34.5)"), enemy->getReceivedMessages()[0]);
			mm->send();
			Assert::AreEqual(static_cast<size_t>(2), enemy->getReceivedMessages().size());
			Assert::AreEqual(std::string("jump()"), enemy->getReceivedMessages()[1]);
		}

		TEST_METHOD(Send0Message) {
			MessageServerPtr mm(new MessageServer());
			std::shared_ptr<MessageClientStub1> enemy(new MessageClientStub1(mm));
			enemy->raiseHand("enemy");

			mm->send();
			Assert::AreEqual(static_cast<size_t>(0), enemy->getReceivedMessages().size());
		}
	};
}