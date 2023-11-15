#include "PlayerModel.hpp"
#include "ModelInstance.hpp"
#include "ModelDatabase.hpp"
#include "MessageParser.hpp"
#include "MessageGenerator.hpp"
#include "Direction.hpp"
#include "DxLib.h"
#include "AABB.hpp"

namespace game {
    PlayerModel::PlayerModel(MessageServerPtr server, ModelDatabasePtr modelDatabase, float scale, const std::string& modelFilename)
        : MessageClient(server)
        , _model(nullptr)
        , _speed(0.0f)
    {
        generateInstance(modelDatabase, modelFilename, scale);
    }

    void PlayerModel::receive(const std::string& message) {
        MessageParser mp(message);

        if (mp.getSignature() == "moveInput") {
            const auto direction = mp.getArgumentAsString(0);
            responseMove(direction);
        }
        else if (mp.getSignature() == "setSpeed") {
            _speed = mp.getArgumentAsDouble(0);
        }
    }

    void PlayerModel::draw() const {
        _model->draw();
    }

    void PlayerModel::generateInstance(ModelDatabasePtr modelDatabase, const std::string& modelFilename, float scale) {
        // リソースの生成
        auto playerResource = modelDatabase->fetch("person", modelFilename);
        // インスタンスの生成
        _model = ModelInstancePtr(new ModelInstance(playerResource));

        _model->setScale(scale);
    }

    void PlayerModel::responseMove(const std::string& direction) {
        // 移動ベクトル生成
        Direction dir(direction);
        VECTOR move;
        move.x = dir.x();
        move.y = 0;
        move.z = dir.y();
        move = VNorm(move);
        move = VScale(move, _speed);

        // メッセージ生成
        MessageGenerator mg;
        mg.setDestination("physics", 0);
        mg.setSignature("playerMove");
        mg.addArgument(getId());
        mg.addArgument(move.x);
        mg.addArgument(move.y);
        mg.addArgument(move.z);
        // 送信
        send(mg.generate());

        // メッセージ生成
        mg.setSignature("playerFace");
        // 送信
        send(mg.generate());
    }
}
