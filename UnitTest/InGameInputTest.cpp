#include "pch.h"
#include "InGameInput.hpp"
#include "InGameInputStub.hpp"
#include "MessageServer.hpp"

namespace game {
	TEST_CLASS(InGameInputTest)
	{
	public:
		TEST_METHOD(Constructor) {
			MessageServerPtr ms(new MessageServer());
			InGameInput input(ms);
			Assert::AreEqual(0ULL, input.size());
		}
		TEST_METHOD(Set1Device) {
			MessageServerPtr ms(new MessageServer());
			InGameInputInterfacePtr device(new InGameInputTrue());
			InGameInput input(ms);

			input.setDevice(0, device);

			Assert::AreEqual(device, input.getDevice(0));
		}
		TEST_METHOD(SetDevicesToSamePlayer) {
			MessageServerPtr ms(new MessageServer());
			InGameInputInterfacePtr device(new InGameInputTrue());
			InGameInputInterfacePtr device2(new InGameInputTrue());
			InGameInput input(ms);

			input.setDevice(0, device);
			input.setDevice(0, device2);

			Assert::AreEqual(device2, input.getDevice(0));
		}
		TEST_METHOD(Set1DeviceTo2Players) {
			MessageServerPtr ms(new MessageServer());
			InGameInputInterfacePtr device(new InGameInputTrue());
			InGameInput input(ms);

			input.setDevice(0, device);
			input.setDevice(1, device);

			Assert::AreEqual(device, input.getDevice(0));
			Assert::AreEqual(device, input.getDevice(1));
		}
		TEST_METHOD(GetNotExistDevice) {
			MessageServerPtr ms(new MessageServer());
			InGameInputInterfacePtr device(new InGameInputTrue());
			InGameInput input(ms);

			input.setDevice(3, device);

			Assert::AreEqual(InGameInputInterfacePtr(nullptr), input.getDevice(0));
			Assert::AreEqual(InGameInputInterfacePtr(nullptr), input.getDevice(1));
			Assert::AreEqual(InGameInputInterfacePtr(nullptr), input.getDevice(2));
			Assert::AreEqual(device, input.getDevice(1));
		}
		TEST_METHOD(GetFromEmpty) {
			MessageServerPtr ms(new MessageServer());
			InGameInputInterfacePtr device(new InGameInputTrue());
			InGameInput input(ms);

			Assert::AreEqual(InGameInputInterfacePtr(nullptr), input.getDevice(0));
			Assert::AreEqual(InGameInputInterfacePtr(nullptr), input.getDevice(1));
		}
		TEST_METHOD(GetFromNotExistPlayer) {
			MessageServerPtr ms(new MessageServer());
			InGameInputInterfacePtr device(new InGameInputTrue());
			InGameInput input(ms);

			input.setDevice(3, device);

			Assert::AreEqual(InGameInputInterfacePtr(nullptr), input.getDevice(6));
		}

		TEST_METHOD(ValidResponseMove) {
			MessageServerPtr ms(new MessageServer());
			InGameInputInterfacePtr device(new InGameInputTrue());
			InGameInput input(ms);

			input.setDevice(0, device);
			input.receive("checkMoveInput(0)");

			Assert::AreEqual(std::string("[Game][0]move(0, left)"), ms->getMessages().front());
		}
		TEST_METHOD(NoneResponseMove) {
			MessageServerPtr ms(new MessageServer());
			InGameInputInterfacePtr device(new InGameInputFalse());
			InGameInput input(ms);

			input.setDevice(0, device);
			input.receive("checkMoveInput(0)");

			Assert::IsTrue(ms->isEmpty());
		}
		TEST_METHOD(ValidResponseGetItem) {
			MessageServerPtr ms(new MessageServer());
			InGameInputInterfacePtr device(new InGameInputTrue());
			InGameInput input(ms);

			input.setDevice(0, device);
			input.receive("checkGetItemInput(0)");

			Assert::AreEqual(std::string("[Game][0]getItem(0)"), ms->getMessages().front());
		}
		TEST_METHOD(NoneResponseGetItem) {
			MessageServerPtr ms(new MessageServer());
			InGameInputInterfacePtr device(new InGameInputFalse());
			InGameInput input(ms);

			input.setDevice(0, device);
			input.receive("checkGetItemInput(0)");

			Assert::IsTrue(ms->isEmpty());
		}
		TEST_METHOD(ValidResponseUseItem) {
			MessageServerPtr ms(new MessageServer());
			InGameInputInterfacePtr device(new InGameInputTrue());
			InGameInput input(ms);

			input.setDevice(0, device);
			input.receive("checkGetItemInput(0)");

			Assert::AreEqual(std::string("[Game][0]useItem(0)"), ms->getMessages().front());
		}
		TEST_METHOD(NoneResponseUseItem) {
			MessageServerPtr ms(new MessageServer());
			InGameInputInterfacePtr device(new InGameInputFalse());
			InGameInput input(ms);

			input.setDevice(0, device);
			input.receive("checkUseItemInput(0)");

			Assert::IsTrue(ms->isEmpty());
		}
		TEST_METHOD(ResponseNotExistDevice) {
			MessageServerPtr ms(new MessageServer());
			InGameInputInterfacePtr device(new InGameInputTrue());
			InGameInput input(ms);

			input.setDevice(3, device);
			input.receive("checkUseItemInput(0)");

			Assert::IsTrue(ms->isEmpty());
		}
		TEST_METHOD(ResponseFromNotExistPlayer) {
			MessageServerPtr ms(new MessageServer());
			InGameInputInterfacePtr device(new InGameInputTrue());
			InGameInput input(ms);

			input.receive("checkUseItemInput(0)");

			Assert::IsTrue(ms->isEmpty());
		}
	};
}
