#include "InGameInputPad.hpp"
#include <stdexcept>

namespace game {
	InGameInputPad::InGameInputPad(int id)
		: _id(id)
	{}

	InGameInputInterface::MOVE_DIRECTION InGameInputPad::move() {
		return static_cast<MOVE_DIRECTION>(getDirection());
	}

	InGameInputInterface::Direction InGameInputPad::getDirection() {
		Direction dir;
		GetJoypadAnalogInput(&dir.x, &dir.y, _id);
		return dir;
	}

	bool InGameInputPad::getSkillItem() {
		XINPUT_STATE inputState = getInputState();
		return inputState.Buttons[XINPUT_BUTTON_B];
	}

	bool InGameInputPad::useSkillItem() {
		XINPUT_STATE inputState = getInputState();
		return inputState.Buttons[XINPUT_BUTTON_A];
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
}
