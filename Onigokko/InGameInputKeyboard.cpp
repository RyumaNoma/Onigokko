#include "InGameInputKeyboard.hpp"
#include "DxLib.h"
#include "MessageParser.hpp"
#include "MessageGenerator.hpp"
#include "Direction.hpp"

namespace game {
    InGameInputKeyboard::InGameInputKeyboard(MessageServerPtr server)
        : MessageClient(server)
    {}

    void InGameInputKeyboard::receive(const std::string & message) {
        MessageParser mp(message);

        if (mp.getSignature() == "checkMoveInput") {
            responseMove();
        }
        else if (mp.getSignature() == "checkGetItemInput") {
            responseGetSkillItem();
        }
        else if (mp.getSignature() == "checkUseItemInput") {
            responseUseSkillItem();
        }
    }

    void InGameInputKeyboard::responseMove() const {
        int x, y;
        // 左右
        if (CheckHitKey(KEY_INPUT_A) && !CheckHitKey(KEY_INPUT_D)) { // 左
            x = -1;
        }
        else if (!CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_D)) { // 右
            x = 1;
        }
        // 上下
        if (CheckHitKey(KEY_INPUT_S) && !CheckHitKey(KEY_INPUT_W)) { // 下
            y = 1;
        }
        else if (!CheckHitKey(KEY_INPUT_S) && CheckHitKey(KEY_INPUT_W)) { // 上
            y = -1;
        }
        Direction dir(x, y);
        auto dirStr = static_cast<std::string>(dir);

        // 移動入力が行われた場合のみ
        if (dirStr != "NONE") {
            MessageGenerator mg;
            mg.setDestination("playerModel", 0);
            mg.setSignature("moveInput");
            mg.addArgument(getId());
            mg.addArgument(dirStr);
        }
    }

    void InGameInputKeyboard::responseGetSkillItem() const {
        // アイテム取得入力があった場合のみ
        if (GetMouseInput() & MOUSE_INPUT_RIGHT) {
            MessageGenerator mg;
            mg.setDestination("player", 0);
            mg.setSignature("getItemInput");
            mg.addArgument(getId());
        }
    }

    void InGameInputKeyboard::responseUseSkillItem() const {
        // アイテム使用入力があった場合のみ
        if (GetMouseInput() & MOUSE_INPUT_LEFT) {
            MessageGenerator mg;
            mg.setDestination("player", 0);
            mg.setSignature("useItemInput");
            mg.addArgument(getId());
        }
    }

}
