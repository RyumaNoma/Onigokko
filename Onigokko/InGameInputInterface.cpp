#include "InGameInputInterface.hpp"

namespace game {
    InGameInputInterface::MOVE_DIRECTION InGameInputInterface::operator()(const Direction& dir) {
        if (dir.x < 0) { // ������
            if (dir.y < 0) { // ����
                return MOVE_DIRECTION::LEFT_DOWN;
            }
            else if (dir.y > 0) { // ����
                return MOVE_DIRECTION::LEFT_UP;
            }
            else { // ��
                return MOVE_DIRECTION::LEFT;
            }
        }
        else if (dir.x > 0) { // �E����
            if (dir.y < 0) { // �E��
                return MOVE_DIRECTION::RIGHT_DOWN;
            }
            else if (dir.y > 0) { // �E��
                return MOVE_DIRECTION::RIGHT_UP;
            }
            else { // �E
                return MOVE_DIRECTION::RIGHT;
            }
        }
        else {
            if (dir.y < 0) { // ��
                return MOVE_DIRECTION::DOWN;
            }
            else if (dir.y > 0) { // ��
                return MOVE_DIRECTION::UP;
            }
            else { // ��
                return MOVE_DIRECTION::NONE;
            }
        }
    }
}
