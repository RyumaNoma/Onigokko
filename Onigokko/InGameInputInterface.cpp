#include "InGameInputInterface.hpp"

namespace game {
    InGameInputInterface::Direction::operator InGameInputInterface::MOVE_DIRECTION() const {
        if (x < 0) { // 左方向
            if (y < 0) { // 左下
                return MOVE_DIRECTION::LEFT_DOWN;
            }
            else if (y > 0) { // 左上
                return MOVE_DIRECTION::LEFT_UP;
            }
            else { // 左
                return MOVE_DIRECTION::LEFT;
            }
        }
        else if (x > 0) { // 右方向
            if (y < 0) { // 右下
                return MOVE_DIRECTION::RIGHT_DOWN;
            }
            else if (y > 0) { // 右上
                return MOVE_DIRECTION::RIGHT_UP;
            }
            else { // 右
                return MOVE_DIRECTION::RIGHT;
            }
        }
        else {
            if (y < 0) { // 下
                return MOVE_DIRECTION::DOWN;
            }
            else if (y > 0) { // 上
                return MOVE_DIRECTION::UP;
            }
            else { // 無
                return MOVE_DIRECTION::NONE;
            }
        }
    }
}
