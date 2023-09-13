#include "InGameInputKeyboard.hpp"
#include "DxLib.h"

namespace game {
	InGameInputInterface::MOVE_DIRECTION InGameInputKeyboard::move() {
        return static_cast<MOVE_DIRECTION>(getDirectionWASD());
	}

	InGameInputInterface::Direction InGameInputKeyboard::getDirection() {
        return getDirectionWASD();
	}

	bool InGameInputKeyboard::getSkillItem() {
        return (GetMouseInput() & MOUSE_INPUT_RIGHT);
	}

	bool InGameInputKeyboard::useSkillItem() {
        return (GetMouseInput() & MOUSE_INPUT_LEFT);
	}

	InGameInputInterface::Direction InGameInputKeyboard::getDirectionWASD() {
        Direction dir;
        // 左右
        if (CheckHitKey(KEY_INPUT_A)) { // 左方向
            dir.x = -1;
        }
        else if (CheckHitKey(KEY_INPUT_D)) { // 右方向
            dir.x = 1;
        }
        // 上下
        if (CheckHitKey(KEY_INPUT_S)) { // 下
            dir.y = -1;
        }
        else if (CheckHitKey(KEY_INPUT_W)) { // 上
            dir.y = 1;
        }

        return dir;
	}
}
