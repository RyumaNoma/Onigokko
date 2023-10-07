#pragma once
#include <string>

namespace game {
	/**
	 * @brief 2次元のスティック入力の方向。
	 * @attention x(右方向が+)、y(上方向が+)
	 */
	class Direction {
	public:
		Direction();
		Direction(int x, int y);

		explicit operator std::string() const;

		int x() const { return _x; }
		int y() const { return _y; }
	private:
		int _x, _y;
	};
}
