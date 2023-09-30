#pragma once
#include <vector>
#include "InGameInputInterface.hpp"

namespace game {
	class InGameInputTrue
		: public InGameInputInterface
	{
	public:
		virtual MOVE_DIRECTION move() override;
		virtual Direction getDirection() override;
		virtual bool getSkillItem() override;
		virtual bool useSkillItem() override;
	};
	class InGameInputFalse
		: public InGameInputInterface
	{
	public:
		virtual MOVE_DIRECTION move() override;
		virtual Direction getDirection() override;
		virtual bool getSkillItem() override;
		virtual bool useSkillItem() override;
	};
}
