#include "InGameInputInterface.hpp"
#include <cmath>
#include "DxLib.h"

namespace game {
    InGameInputInterface::Direction::operator InGameInputInterface::MOVE_DIRECTION() const {
        if (x == 0 && y == 0) { return MOVE_DIRECTION::NONE; }
        double angle = std::atan2(y, x);
        constexpr float UNIT = DX_PI_F / 8.0f;

        if (angle <= -UNIT * 7) {
            return MOVE_DIRECTION::LEFT;
        }
        else if (angle <= -UNIT * 5) {
            return MOVE_DIRECTION::LEFT_UP;
        }
        else if (angle <= -UNIT * 3) {
            return MOVE_DIRECTION::UP;
        }
        else if (angle <= -UNIT) {
            return MOVE_DIRECTION::RIGHT_UP;
        }
        if (angle <= UNIT) {
            return MOVE_DIRECTION::RIGHT;
        }
        else if (angle <= UNIT * 3) {
            return MOVE_DIRECTION::RIGHT_DOWN;
        }
        else if (angle <= UNIT * 5) {
            return MOVE_DIRECTION::DOWN;
        }
        else if (angle <= UNIT * 7) {
            return MOVE_DIRECTION::LEFT_DOWN;
        }
        else {
            return MOVE_DIRECTION::LEFT;
        }
    }
}
