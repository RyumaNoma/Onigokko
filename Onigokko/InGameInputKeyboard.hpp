#pragma once
#include "InGameInputInterface.hpp"

namespace game {
	class InGameInputKeyboard
		: public InGameInputInterface {
	public:
		virtual MOVE_DIRECTION move() override;

		virtual Direction getDirection() override;

		virtual bool getSkillItem() override;

		virtual bool useSkillItem() override;
	};
}
