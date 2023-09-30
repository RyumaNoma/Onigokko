#include "pch.h"
#include "InGameInput.hpp"
#include "InGameInputTestStub.hpp"
#include "MessageServer.hpp"

namespace game {
	TEST_CLASS(InGameInputTest)
	{
	public:
		TEST_METHOD(Constructor) {
			MessageServerPtr ms;
			InGameInput input(ms);
			Assert::AreEqual(0ULL, input.size());
		}
		TEST_METHOD(Set1Device) {
			MessageServerPtr ms;
			InGameInput input(ms);

			input.setDevice(0, )
		}
		TEST_METHOD(SetDevicesToSamePlayer) {

		}
		TEST_METHOD(Set1DeviceTo2Players) {

		}
		TEST_METHOD(GetNotExistDevice) {

		}
		TEST_METHOD(GetFromEmpty) {

		}
		TEST_METHOD(GetFromNotExistPlayer) {

		}

		TEST_METHOD(ResponseMove) {

		}
		TEST_METHOD(ResponseGetItem) {

		}
		TEST_METHOD(ResponseUseItem) {

		}
		TEST_METHOD(ResponseNotExistDevice) {

		}
		TEST_METHOD(ResponseFromNotExistPlayer) {

		}
	};
}
