#include "pch.h"
#include "MessageParser.hpp"

namespace game {
	TEST_CLASS(MessageParserTest)
	{
	public:
		TEST_METHOD(Parse0ArgumentsTest) {
			MessageParser mp("[enemy][3]die()");

			Assert::AreEqual(std::string("enemy"), mp.getDestination());
			Assert::AreEqual(3, mp.getDestinationId());
			Assert::AreEqual(std::string("die"), mp.getSignature());
			try {
				mp.getArgumentAsString(0);
			}
			catch (std::out_of_range) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(Parse1ArgumentsTest) {
			MessageParser mp("[enemy][3]die(letsgo)");

			Assert::AreEqual(std::string("enemy"), mp.getDestination());
			Assert::AreEqual(3, mp.getDestinationId());
			Assert::AreEqual(std::string("die"), mp.getSignature());
			Assert::AreEqual(std::string("letsgo"), mp.getArgumentAsString(0));
			try {
				mp.getArgumentAsString(1);
			}
			catch (std::out_of_range) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(Parse2ArgumentsTest) {
			MessageParser mp("[enemy][3]die(letsgo, qw)");

			Assert::AreEqual(std::string("enemy"), mp.getDestination());
			Assert::AreEqual(3, mp.getDestinationId());
			Assert::AreEqual(std::string("die"), mp.getSignature());
			Assert::AreEqual(std::string("letsgo"), mp.getArgumentAsString(0));
			Assert::AreEqual(std::string(" qw"), mp.getArgumentAsString(1));
			try {
				mp.getArgumentAsString(2);
			}
			catch (std::out_of_range) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();

		}
		TEST_METHOD(IntegerArgumentsTest) {
			MessageParser mp("[enemy][3]die(yo,34)");

			Assert::AreEqual(std::string("enemy"), mp.getDestination());
			Assert::AreEqual(3, mp.getDestinationId());
			Assert::AreEqual(std::string("die"), mp.getSignature());
			Assert::AreEqual(std::string("yo"), mp.getArgumentAsString(0));
			Assert::AreEqual(34, mp.getArgumentAsInteger(1));
			try {
				mp.getArgumentAsString(2);
			}
			catch (std::out_of_range) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(DoubleArgumentsTest) {
			MessageParser mp("[enemy][3]die(yo,0.456)");

			Assert::AreEqual(std::string("enemy"), mp.getDestination());
			Assert::AreEqual(3, mp.getDestinationId());
			Assert::AreEqual(std::string("die"), mp.getSignature());
			Assert::AreEqual(std::string("yo"), mp.getArgumentAsString(0));
			Assert::AreEqual(0.456, mp.getArgumentAsDouble(1));
			try {
				mp.getArgumentAsString(2);
			}
			catch (std::out_of_range) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(ParseNotIntegerAsInteger) {
			MessageParser mp("[enemy][3]die(yo)");

			Assert::AreEqual(std::string("enemy"), mp.getDestination());
			Assert::AreEqual(3, mp.getDestinationId());
			Assert::AreEqual(std::string("die"), mp.getSignature());
			Assert::AreEqual(std::string("yo"), mp.getArgumentAsString(0));
			try {
				mp.getArgumentAsString(0);
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(ParserIntegerAsDouble) {
			MessageParser mp("[enemy][3]die(45)");

			Assert::AreEqual(std::string("enemy"), mp.getDestination());
			Assert::AreEqual(3, mp.getDestinationId());
			Assert::AreEqual(std::string("die"), mp.getSignature());
			Assert::AreEqual(std::string("45"), mp.getArgumentAsString(0));
			Assert::AreEqual(45.0, mp.getArgumentAsDouble(1));
		}
		TEST_METHOD(BroadcastMessageTest) {
			MessageParser mp("[enemy][Broadcast]die()");

			Assert::AreEqual(std::string("enemy"), mp.getDestination());
			Assert::AreEqual(-1, mp.getDestinationId());
			Assert::IsTrue(mp.isBroadcast());
			Assert::AreEqual(std::string("die"), mp.getSignature());
		}
		TEST_METHOD(IdMessageTest) {
			MessageParser mp("[enemy][0]die()");

			Assert::AreEqual(std::string("enemy"), mp.getDestination());
			Assert::AreEqual(0, mp.getDestinationId());
			Assert::IsFalse(mp.isBroadcast());
			Assert::AreEqual(std::string("die"), mp.getSignature());
		}
	};
}