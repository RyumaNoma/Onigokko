#include "pch.h"
#include "InGameInputStub.hpp"

namespace game {
	InGameInputInterface::MOVE_DIRECTION InGameInputTrue::move()
	{
		return MOVE_DIRECTION::LEFT;
	}
	InGameInputInterface::Direction InGameInputTrue::getDirection()
	{
		return Direction(1, 0);
	}
	bool InGameInputTrue::getSkillItem()
	{
		return true;
	}
	bool InGameInputTrue::useSkillItem()
	{
		return true;
	}
	InGameInputInterface::MOVE_DIRECTION InGameInputFalse::move()
	{
		return MOVE_DIRECTION::NONE;
	}
	InGameInputInterface::Direction InGameInputFalse::getDirection()
	{
		return Direction(0, 0);
	}
	bool InGameInputFalse::getSkillItem()
	{
		return false;
	}
	bool InGameInputFalse::useSkillItem()
	{
		return false;
	}
}
