#include "InGameInputInterface.hpp"

namespace game {
    InGameInputInterface::MOVE_DIRECTION InGameInputInterface::operator()(const Direction& dir) {
        if (dir.x < 0) { // 左方向
            if (dir.y < 0) { // 左下
                return MOVE_DIRECTION::LEFT_DOWN;
            }
            else if (dir.y > 0) { // 左上
                return MOVE_DIRECTION::LEFT_UP;
            }
            else { // 左
                return MOVE_DIRECTION::LEFT;
            }
        }
        else if (dir.x > 0) { // 右方向
            if (dir.y < 0) { // 右下
                return MOVE_DIRECTION::RIGHT_DOWN;
            }
            else if (dir.y > 0) { // 右上
                return MOVE_DIRECTION::RIGHT_UP;
            }
            else { // 右
                return MOVE_DIRECTION::RIGHT;
            }
        }
        else {
            if (dir.y < 0) { // 下
                return MOVE_DIRECTION::DOWN;
            }
            else if (dir.y > 0) { // 上
                return MOVE_DIRECTION::UP;
            }
            else { // 無
                return MOVE_DIRECTION::NONE;
            }
        }
    }
}
