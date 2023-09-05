#include "pch.h"
#include "MessageManager.hpp"
#include "MessageCommunicatorStub.hpp"

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<> inline std::wstring ToString<game::MessageCommunicatorPtr>(const game::MessageCommunicatorPtr& t) {
				RETURN_WIDE_STRING(t.get());
			}
		}
	}
}

namespace game {
	class Enemy;
	class GameObject;

	TEST_CLASS(MessageManagerTest) {
	public:
		TEST_METHOD(DefaultConstructor) {
			MessageManager mm;

			Assert::IsTrue(mm.getMessages().empty());
			Assert::IsTrue(mm.getCommunicators().empty());
		}

		TEST_METHOD(setValidCommunicator) {
			MessageManagerPtr mm(new MessageManager());
			MessageCommunicatorPtr enemy(new Enemy(mm));
			MessageCommunicatorPtr gameObj(new GameObject(mm));

			mm->setCommunicator("enemy", 1, enemy);
			mm->setCommunicator("gameObj", 1, gameObj);

			Assert::AreEqual(enemy, mm->getCommunicator("enemy", 1));
			Assert::AreEqual(gameObj, mm->getCommunicator("gameObj", 1));
		};

		TEST_METHOD(setNullCommunicator) {
			MessageManagerPtr mm(new MessageManager());
			MessageCommunicatorPtr enemy(nullptr);

			try {
				mm->setCommunicator("enemy", 1, enemy);
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}

		TEST_METHOD(setCommunicatorSameTagId) {
			MessageManagerPtr mm(new MessageManager());
			MessageCommunicatorPtr enemy1(new Enemy(mm));
			MessageCommunicatorPtr enemy2(new Enemy(mm));

			mm->setCommunicator("enemy", 1, enemy1);
			mm->setCommunicator("enemy", 1, enemy2);

			Assert::AreEqual(enemy2, mm->getCommunicator("enemy", 1));
		}

		TEST_METHOD(getNotexistCommunicator) {
			MessageManagerPtr mm(new MessageManager());
			MessageCommunicatorPtr enemy(new Enemy(mm));
			MessageCommunicatorPtr gameObj(new GameObject(mm));

			mm->setCommunicator("enemy", 1, enemy);

			Assert::AreEqual(enemy, mm->getCommunicator("enemy", 1));
			Assert::AreEqual(MessageCommunicatorPtr(nullptr), mm->getCommunicator("enemy", 2));
			Assert::AreEqual(MessageCommunicatorPtr(nullptr), mm->getCommunicator("enemy", -1));
			Assert::AreEqual(MessageCommunicatorPtr(nullptr), mm->getCommunicator("enemy", -1));
			Assert::AreEqual(MessageCommunicatorPtr(nullptr), mm->getCommunicator("gameObj", 1));
		}

		TEST_METHOD(setMinusIdCommunicator) {
			MessageManagerPtr mm(new MessageManager());
			MessageCommunicatorPtr enemy(new Enemy(mm));

			try {
				mm->setCommunicator("enemy", -1, enemy);
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}

		TEST_METHOD(eraseValidCommunicator) {
			MessageManagerPtr mm(new MessageManager());
			std::shared_ptr<Enemy> enemy(new Enemy(mm));
			mm->setCommunicator("enemy", 0, enemy);
			mm->eraseCommunicator("enemy", 0);
			Assert::AreEqual(MessageCommunicatorPtr(nullptr), mm->getCommunicator("enemy", 0));
		}

		TEST_METHOD(eraseNotExistTagCommunicator) {
			MessageManagerPtr mm(new MessageManager());
			std::shared_ptr<Enemy> enemy(new Enemy(mm));
			mm->setCommunicator("enemy", 0, enemy);
			mm->eraseCommunicator("you", 0);
			Assert::AreEqual(MessageCommunicatorPtr(enemy), mm->getCommunicator("enemy", 0));
			Assert::AreEqual(MessageCommunicatorPtr(nullptr), mm->getCommunicator("you", 0));
		}

		TEST_METHOD(eraseNotExistIdCommunicator) {
			MessageManagerPtr mm(new MessageManager());
			std::shared_ptr<Enemy> enemy(new Enemy(mm));
			mm->setCommunicator("enemy", 0, enemy);
			mm->eraseCommunicator("enemy", 12);
			Assert::AreEqual(MessageCommunicatorPtr(enemy), mm->getCommunicator("enemy", 0));
			Assert::AreEqual(MessageCommunicatorPtr(nullptr), mm->getCommunicator("enemy", 12));
		}

		TEST_METHOD(eraseCommunicatorTwice) {
			MessageManagerPtr mm(new MessageManager());
			std::shared_ptr<Enemy> enemy(new Enemy(mm));
			mm->setCommunicator("enemy", 0, enemy);
			mm->eraseCommunicator("enemy", 0);
			mm->eraseCommunicator("enemy", 0);
			Assert::AreEqual(MessageCommunicatorPtr(nullptr), mm->getCommunicator("enemy", 0));
		}

		TEST_METHOD(ReceiveValidMessage) {
			MessageManagerPtr mm(new MessageManager());
			mm->receive("[enemy][1]die()");
		}

		TEST_METHOD(ReceiveInvalidMessage) {
			MessageManagerPtr mm(new MessageManager());
			mm->receive("[e)");
			mm->receive("");
		}

		TEST_METHOD(SendMultipleMessages) {
			MessageManagerPtr mm(new MessageManager());
			std::shared_ptr<Enemy> enemy(new Enemy(mm));
			const std::string msg1 = "die()";
			const std::string msg2 = "jump(11)";
			mm->setCommunicator("enemy", 1, enemy);
			mm->receive("[enemy][1]" + msg1);
			mm->receive("[enemy][1]" + msg2);
			mm->sendAll();

			Assert::AreEqual(static_cast<size_t>(2), enemy->getReceivedMessages().size());
			Assert::AreEqual(msg1, enemy->getReceivedMessage(0));
			Assert::AreEqual(msg2, enemy->getReceivedMessage(1));
		}
		
		TEST_METHOD(SendInvalidMessages) {
			MessageManagerPtr mm(new MessageManager());
			std::shared_ptr<Enemy> enemy(new Enemy(mm));
			mm->setCommunicator("enemy", 0, enemy);
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
		
		TEST_METHOD(SendMessagesBroadcast) {
			MessageManagerPtr mm(new MessageManager());
			std::shared_ptr<Enemy> enemy(new Enemy(mm));
			const std::string msg = "run(34.5)";
			mm->setCommunicator("enemy", 0, enemy);
			mm->setCommunicator("enemy", 1, enemy);
			mm->receive("[enemy][Broadcast]" + msg);
			mm->sendAll();

			Assert::AreEqual(static_cast<size_t>(2), enemy->getReceivedMessages().size());
			Assert::AreEqual(msg, enemy->getReceivedMessage(0));
			Assert::AreEqual(msg, enemy->getReceivedMessage(1));
		}
		
		TEST_METHOD(SendMessageToNotExistTag) {
			MessageManagerPtr mm(new MessageManager());
			std::shared_ptr<Enemy> enemy(new Enemy(mm));
			mm->setCommunicator("enemy", 0, enemy);
			mm->receive("[you][1]run(34.5)");
			mm->sendAll();

			Assert::IsTrue(enemy->getReceivedMessages().empty());
		}
		
		TEST_METHOD(SendMessageToNotExistTagBroadcast) {
			MessageManagerPtr mm(new MessageManager());
			std::shared_ptr<Enemy> enemy(new Enemy(mm));
			mm->setCommunicator("enemy", 0, enemy);
			mm->receive("[you][Broadcast]run(34.5)");
			mm->sendAll();

			Assert::IsTrue(enemy->getReceivedMessages().empty());
		}
		
		TEST_METHOD(SendMessageToNotExistCommunicator) {
			MessageManagerPtr mm(new MessageManager());
			std::shared_ptr<Enemy> enemy(new Enemy(mm));
			mm->setCommunicator("enemy", 0, enemy);
			mm->receive("[enemy][1]run(34.5)");
			mm->sendAll();

			Assert::IsTrue(enemy->getReceivedMessages().empty());
		}
		
		TEST_METHOD(Send0Messages) {
			MessageManagerPtr mm(new MessageManager());
			std::shared_ptr<Enemy> enemy(new Enemy(mm));
			mm->setCommunicator("enemy", 0, enemy);
			mm->sendAll();
		}
	};
}