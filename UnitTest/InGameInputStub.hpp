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
	using InGameInputTruePtr = std::shared_ptr<InGameInputTrue>;
	using InGameInputTrueRef = std::shared_ptr<InGameInputTrue>;

	class InGameInputFalse
		: public InGameInputInterface
	{
	public:
		virtual MOVE_DIRECTION move() override;
		virtual Direction getDirection() override;
		virtual bool getSkillItem() override;
		virtual bool useSkillItem() override;
	};
	using InGameInputFalsePtr = std::shared_ptr<InGameInputFalse>;
	using InGameInputFalseRef = std::shared_ptr<InGameInputFalse>;
}
