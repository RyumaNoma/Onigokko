#include "pch.h"
#include "MessageGenerator.hpp"

namespace game
{
	TEST_CLASS(MessageGeneratorTest)
	{
	public:
		TEST_METHOD(DefaultConstructorAttributes) {
			MessageGenerator mg;
			Assert::IsFalse(mg.isBroadcast());
			Assert::AreEqual(0, mg.getDestinationId());
			Assert::AreEqual(std::string(""), mg.getSignature());
			Assert::IsTrue(mg.getArguments().empty());
		}

		TEST_METHOD(SetBroadcast) {
			MessageGenerator mg;
			mg.setDestinationBroadcast("enemy");
			
			Assert::IsTrue(mg.isBroadcast());
			Assert::AreEqual(-1, mg.getDestinationId());
		}

		TEST_METHOD(SetValidDestinationId) {
			MessageGenerator mg;
			mg.setDestination("enemy", 1);

			Assert::AreEqual(1, mg.getDestinationId());
		}

		TEST_METHOD(SetMinusDestinationId) {
			MessageGenerator mg;
			
			try {
				mg.setDestination("you", -1);
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}

		TEST_METHOD(setSigunature) {
			MessageGenerator mg;
			mg.setSignature("addScore");
			Assert::AreEqual(std::string("addScore"), mg.getSignature());
		}

		TEST_METHOD(setSignatureIncludingSpace) {
			MessageGenerator mg;
			// 先頭
			{
				try {
					mg.setSignature(" helloworld!");
				}
				catch (std::invalid_argument) {
					return;
				}
				catch (...) {
					Assert::Fail();
				}
				Assert::Fail();
			}
			// 中間
			{
				try {
					mg.setSignature("hello world!");
				}
				catch (std::invalid_argument) {
					return;
				}
				catch (...) {
					Assert::Fail();
				}
				Assert::Fail();
			}
			// 最後
			{
				try {
					mg.setSignature("helloworld! ");
				}
				catch (std::invalid_argument) {
					return;
				}
				catch (...) {
					Assert::Fail();
				}
				Assert::Fail();
			}
		}

		TEST_METHOD(setSignatureIncludingTabSpace) {
			MessageGenerator mg;
			// 先頭
			{
				try {
					mg.setSignature("	helloworld!");
				}
				catch (std::invalid_argument) {
					return;
				}
				catch (...) {
					Assert::Fail();
				}
				Assert::Fail();
			}
			// 中間
			{
				try {
					mg.setSignature("hello	world!");
				}
				catch (std::invalid_argument) {
					return;
				}
				catch (...) {
					Assert::Fail();
				}
				Assert::Fail();
			}
			// 最後
			{
				try {
					mg.setSignature("helloworld!	");
				}
				catch (std::invalid_argument) {
					return;
				}
				catch (...) {
					Assert::Fail();
				}
				Assert::Fail();
			}
		}

		TEST_METHOD(setSignatureIncludingExcapeCharactor) {
			MessageGenerator mg;
			// 先頭
			{
				try {
					mg.setSignature("\nhello");
				}
				catch (std::invalid_argument) {
					return;
				}
				catch (...) {
					Assert::Fail();
				}
				Assert::Fail();
			}
			// 中間
			{
				try {
					mg.setSignature("he\nllo");
				}
				catch (std::invalid_argument) {
					return;
				}
				catch (...) {
					Assert::Fail();
				}
				Assert::Fail();
			}
			// 最後
			{
				try {
					mg.setSignature("hello\n");
				}
				catch (std::invalid_argument) {
					return;
				}
				catch (...) {
					Assert::Fail();
				}
				Assert::Fail();
			}
		}

		TEST_METHOD(AddValidArgument) {
			MessageGenerator mg;

			mg.addArgument(3);
			mg.addArgument("enemy");
			mg.addArgument(4.0);

			Assert::AreEqual(static_cast<size_t>(3), mg.getArguments().size());
			Assert::AreEqual(std::string("3"), mg.getArgument(0));
			Assert::AreEqual(std::string("enemy"), mg.getArgument(0));
			Assert::AreEqual(std::string("4.0"), mg.getArgument(0));
		}

		TEST_METHOD(UpdateValidArgument) {
			MessageGenerator mg;

			mg.addArgument(3);
			mg.addArgument("enemy");
			mg.addArgument(4.0);

			mg.updateArgument(0, 54);
			mg.updateArgument(1, 2.5);
			mg.updateArgument(2, "hello");
		}

		TEST_METHOD(UpdateUnexistArgument) {
			MessageGenerator mg;
			// 存在しない
			{
				try {
					mg.updateArgument(0, 12);
				}
				catch (std::out_of_range) {
					return;
				}
				catch (...) {
					Assert::Fail();
				}
				Assert::Fail();
			}
			// マイナス
			{
				try {
					mg.updateArgument(-1, 12);
				}
				catch (std::out_of_range) {
					return;
				}
				catch (...) {
					Assert::Fail();
				}
				Assert::Fail();
			}
		}

		TEST_METHOD(BroadcastMessageGenerate) {
			MessageGenerator mg;

			mg.setDestinationBroadcast("enemy");
			mg.setSignature("kill");

			Assert::AreEqual(std::string("[enemy][Broadcast]kill()"), mg.generate());
		}

		TEST_METHOD(DestinationIdMessageGenerate) {
			MessageGenerator mg;

			mg.setDestination("enemy", 12);
			mg.setSignature("kill");
			mg.addArgument("asdf");

			Assert::AreEqual(std::string("[enemy][12]kill(asdf)"), mg.generate());
		}

		TEST_METHOD(EmptyDestinationTagGenerate) {
			MessageGenerator mg;

			mg.setSignature("kill");
			mg.addArgument("asdf");

			try {
				mg.generate();
			}
			catch (std::runtime_error) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}

		TEST_METHOD(EmptySignatureGenerate) {
			MessageGenerator mg;

			mg.setDestination("enemy", 12);
			mg.addArgument("asdf");

			try {
				mg.generate();
			}
			catch (std::runtime_error) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}

		TEST_METHOD(MultipleArgumentsGenerate) {
			MessageGenerator mg;

			mg.setDestination("enemy", 12);
			mg.setSignature("kill");
			mg.addArgument("asdf");
			mg.addArgument(13);

			Assert::AreEqual(std::string("[enemy][12]kill(asdf, 12)"), mg.generate());
		}
	};
}
