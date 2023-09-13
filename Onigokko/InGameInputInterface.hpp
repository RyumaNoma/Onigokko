#pragma once
#include <utility>

namespace game {
	class InGameInputInterface {
	public:
		enum class MOVE_DIRECTION {
			NONE,
			LEFT,
			RIGHT,
			UP,
			DOWN,
			LEFT_UP,
			LEFT_DOWN,
			RIGHT_UP,
			RIGHT_DOWN
		};
		struct Direction {
			int x, y;

			Direction() : x(0), y(0) {}
			Direction(int x, int y) : x(x), y(y) {}
			explicit operator InGameInputInterface::MOVE_DIRECTION() const;
		};

		virtual ~InGameInputInterface() {}

		virtual MOVE_DIRECTION move() = 0;
		virtual Direction getDirection() = 0;
		virtual bool getSkillItem() = 0;
		virtual bool useSkillItem() = 0;
	};
}
