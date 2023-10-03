#include "pch.h"
#include "MapParser.hpp"
#include <stdexcept>

namespace game {
	TEST_CLASS(MapParserTest)
	{
	public:
		TEST_METHOD(ValidFile) {
			MapParser mp("../../UnitTest/ingameConfig.txt");
		}
		TEST_METHOD(NotExistFile) {
			try {
				MapParser mp("hello.txt");
			}
			catch (std::invalid_argument) {
				return;
			}
			catch (...) {
				Assert::Fail();
			}
			Assert::Fail();
		}
		TEST_METHOD(ExistKey) {
			MapParser mp("../../UnitTest/ingameConfig.txt");

			Assert::IsTrue(mp.isExist("OniSpeed"));
			Assert::IsTrue(mp.isExist("name"));
			Assert::IsTrue(mp.isExist("34r"));
		}
		TEST_METHOD(NotExistKey) {
			MapParser mp("../../UnitTest/ingameConfig.txt");
			
			Assert::IsFalse(mp.isExist("hello"));
			Assert::IsFalse(mp.isExist("onispeed"));
		}
		TEST_METHOD(ValidGetQuery) {
			MapParser mp("../../UnitTest/ingameConfig.txt");

			// OniSpeed
			Assert::AreEqual(std::string("100"), mp.getAsString("OniSpeed"));
			Assert::AreEqual(100, mp.getAsInteger("OniSpeed"));
			Assert::AreEqual(100.0f, mp.getAsFloat("OniSpeed"));
			// name
			Assert::AreEqual(std::string("letsgo"), mp.getAsString("name"));
			// 34r
			Assert::AreEqual(std::string("123.222"), mp.getAsString("34r"));
			Assert::AreEqual(123, mp.getAsInteger("34r"));
			Assert::AreEqual(123.222f, mp.getAsFloat("34r"));
		}
		TEST_METHOD(InValidQuery) {
			MapParser mp("../../UnitTest/ingameConfig.txt");

			try {
				mp.getAsInteger("name");
			}
			catch (...) {
				return;
			}
			Assert::Fail();
		}
		TEST_METHOD(DefaultValue) {
			MapParser mp("../../UnitTest/ingameConfig.txt");

			Assert::AreEqual(std::string(""), mp.getAsString("notexistkey"));
			Assert::AreEqual(0, mp.getAsInteger("notexistkey"));
			Assert::AreEqual(0.0f, mp.getAsFloat("notexistkey"));

			Assert::AreEqual(std::string("unchi"), mp.getAsString("notexistkey", "unchi"));
			Assert::AreEqual(-1, mp.getAsInteger("notexistkey", -1));
			Assert::AreEqual(213.2f, mp.getAsFloat("notexistkey", 213.2f));
		}
	};
}
