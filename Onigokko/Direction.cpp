#include "Direction.hpp"
#include "DxLib.h"
#include <cmath>

namespace game {
	Direction::Direction()
		: _x(0)
		, _y(0)
	{}

	Direction::Direction(int x, int y)
		: _x(x)
		, _y(y)
	{}

	Direction::operator std::string() const {
		if (_x == 0 && _y == 0) { return "NONE"; }
		const float angle = std::atan2f(_y, _x);
		constexpr float UNIT = DX_PI_F / 8.0f;

		if (angle <= -UNIT * 7) {
			return "LEFT";
		}
		else if (angle <= -UNIT * 5) {
			return "LEFT_DOWN";
		}
		else if (angle <= -UNIT * 3) {
			return "DOWN";
		}
		else if (angle <= -UNIT) {
			return "RIGHT_DOWN";
		}
		else if (angle <= UNIT) {
			return "RIGHT";
		}
		else if (angle <= UNIT * 3) {
			return "RIGHT_UP";
		}
		else if (angle <= UNIT * 5) {
			return "UP";
		}
		else if (angle <= UNIT * 7) {
			return "LEFT_UP";
		}
		else {
			return "LEFT";
		}
	}


}