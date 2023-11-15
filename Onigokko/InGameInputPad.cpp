#include "InGameInputPad.hpp"
#include "Direction.hpp"
#include "MessageGenerator.hpp"
#include "MessageParser.hpp"
#include <stdexcept>

namespace game {
	InGameInputPad::InGameInputPad(int padId, MessageServerPtr server)
		: _padId(padId)
		, MessageClient(server)
	{}

	void InGameInputPad::receive(const std::string & message) {
		MessageParser mp(message);
		
		if (mp.getSignature() == "checkMoveInput") {
			responseMove();
		}
		else if (mp.getSignature() == "checkGetItemInput") {
			responseGetSkillItem();
		}
		else if (mp.getSignature() == "checkUseItemInput") {
			responseUseSkillItem();
		}
	}

	void InGameInputPad::setDeadZone(double zone) {
		SetJoypadDeadZone(_id, zone);
	}

	XINPUT_STATE InGameInputPad::getInputState() const {
		XINPUT_STATE inputState;
		int success = GetJoypadXInputState(_id, &inputState);
		if (success == -1) { throw std::runtime_error("could not get XInput state"); }
		return inputState;
	}
	
	void InGameInputPad::responseMove() const {
		int x, y;
		GetJoypadAnalogInput(&x, &y, _id);
		Direction dir(x, -y);
		auto dirStr = static_cast<std::string>(dir);

		// 移動入力が行われた場合のみ
		if (dirStr != "NONE") {
			MessageGenerator mg;
			mg.setDestination("playerModel", 0);
			mg.setSignature("moveInput");
			mg.addArgument(getId());
			mg.addArgument(dirStr);
		}
	}

	void InGameInputPad::responseGetSkillItem() const {
		XINPUT_STATE inputState = getInputState();
		
		// アイテム取得入力があった場合のみ
		if (inputState.Buttons[XINPUT_BUTTON_B]) {
			MessageGenerator mg;
			mg.setDestination("player", 0);
			mg.setSignature("getItemInput");
			mg.addArgument(getId());
		}
	}

	void InGameInputPad::responseUseSkillItem() const {
		XINPUT_STATE inputState = getInputState();

		// アイテム使用入力があった場合のみ
		if (inputState.Buttons[XINPUT_BUTTON_A]) {
			MessageGenerator mg;
			mg.setDestination("player", 0);
			mg.setSignature("useItemInput");
			mg.addArgument(getId());
		}
	}
}
