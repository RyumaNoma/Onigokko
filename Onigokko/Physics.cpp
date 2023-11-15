#include "Physics.hpp"
#include "MessageParser.hpp"
#include "MessageGenerator.hpp"
#include "AABB.hpp"
#include "ModelInstance.hpp"
#include "ModelDatabase.hpp"
#include "CollisionDetection.hpp"
#include <cmath>

namespace game {
    Physics::Physics(MessageServerPtr server, ModelDatabasePtr modelDatabase)
        : MessageClient(server)
        , _mdb(modelDatabase)
        , _playerNum(0)
        , _players()
        , _moves()
        , _rotates()
        , _collisionPlayer()
        , _collisionStage()
        , _stages()
    {}

    void Physics::receive(const std::string & message) {
        MessageParser mp(message);

        if (mp.getSignature() == "setPlayerNum") {
            const int playerNum = mp.getArgumentAsInteger(0);
            init(playerNum);
        }
        else if (mp.getSignature() == "playerScale") {
            const int playerId = mp.getArgumentAsInteger(0);
            const int scale = mp.getArgumentAsInteger(1);
            setPlayerScale(playerId, scale);
        }
        else if (mp.getSignature() == "playerPosition") {
            const int playerId = mp.getArgumentAsInteger(0);
            const float x = mp.getArgumentAsDouble(1);
            const float y = mp.getArgumentAsDouble(2);
            const float z = mp.getArgumentAsDouble(3);
            setPlayerPosition(playerId, VGet(x, y, z));
        }
        else if (mp.getSignature() == "playerAnchor") {
            const int playerId = mp.getArgumentAsInteger(0);
            const float x = mp.getArgumentAsDouble(1);
            const float y = mp.getArgumentAsDouble(2);
            const float z = mp.getArgumentAsDouble(3);
            setPlayerAnchor(playerId, VGet(x, y, z));
        }
        else if (mp.getSignature() == "playerMove") {
            const int playerId = mp.getArgumentAsInteger(0);
            const float dx = mp.getArgumentAsDouble(1);
            const float dy = mp.getArgumentAsDouble(2);
            const float dz = mp.getArgumentAsDouble(3);
            setPlayerMove(playerId, VGet(dx, dy, dz));
        }
        else if (mp.getSignature() == "playerFace") {
            const int playerId = mp.getArgumentAsInteger(0);
            const float dx = mp.getArgumentAsDouble(1);
            const float dy = mp.getArgumentAsDouble(2);
            const float dz = mp.getArgumentAsDouble(3);
            setPlayerRotate(playerId, VGet(dx, dy, dz));
        }
        else if (mp.getSignature() == "stageAABB") {
            const int minX = mp.getArgumentAsInteger(0);
            const int minY = mp.getArgumentAsInteger(1);
            const int minZ = mp.getArgumentAsInteger(2);
            const int maxX = mp.getArgumentAsInteger(3);
            const int maxY = mp.getArgumentAsInteger(4);
            const int maxZ = mp.getArgumentAsInteger(5);
            addStageAABB(minX, minY, minZ, maxX, maxY, maxZ);
        }
        else if (mp.getSignature() == "check") {
            check();
        }
        else if (mp.getSignature() == "checkCollision") {
            const int playerId1 = mp.getArgumentAsInteger(0);
            const int playerId2 = mp.getArgumentAsInteger(1);
            responseCheckCollision(playerId1, playerId2);
        }
    }

    void Physics::init(int playerNum) {
        _playerNum = playerNum;
        auto personRef = _mdb->fetch("person", "./person.txt");
        if (_players.empty()) {
            _players.resize(_playerNum, nullptr);
            for (int i = 0; i < _playerNum; ++i) {
                _players.at(i) = ModelInstancePtr(new ModelInstance(personRef));
            }
        }
        _moves.resize(_playerNum, VGet(0, 0, 0));
        _rotates.resize(_playerNum, 0);
        _collisionPlayer.resize(_playerNum, std::vector<float>(_playerNum, 2.0f));
        _collisionStage.resize(_playerNum, std::pair<float, int>(2.0f, -1));
    }

    void Physics::setPlayerScale(int playerId, float scale) {
        _players.at(playerId)->setScale(scale);
    }

    void Physics::setPlayerPosition(int playerId, VECTOR position) {
        _players.at(playerId)->moveTo(position);
    }

    void Physics::setPlayerAnchor(int playerId, VECTOR anchor) {
        _players.at(playerId)->setAnchor(anchor);
    }

    std::vector<AABB> Physics::generateAllPlayersAABB() {
        std::vector<AABB> aabb(_playerNum);
        for (int i = 0; i < _playerNum; ++i) {
            aabb[i].update(_players[i]);
        }
        return aabb;
    }

    void Physics::setPlayerMove(int playerId, VECTOR move) {
        _moves.at(playerId) = move;
    }

    void Physics::setPlayerRotate(int playerId, VECTOR face) {
        const VECTOR base = VGet(1, 0, 0);
        const float cos = VDot(base, face) / VSize(face);
        const float rotation = std::acos(cos);
        _rotates.push_back(rotation);
    }

    void Physics::addStageAABB(int minX, int minY, int minZ, int maxX, int maxY, int maxZ) {
        _stages.push_back(AABB());
        const VECTOR min = VGet(minX, minY, minZ);
        const VECTOR max = VGet(maxX, maxY, maxZ);
        _stages.back().update(min, max);
    }

    void Physics::check() {
        const auto playerAABB = generateAllPlayersAABB();
        checkCollisionStage(playerAABB);
        checkCollisionPlayer(playerAABB);
        responseActualMove();
    }
    void Physics::checkCollisionStage(const std::vector<AABB>& playerAABB) {
        for (int pid = 0; pid < _playerNum; ++pid) {
            auto& player = playerAABB.at(pid);
            auto& move = _moves.at(pid);
            for (int s = 0; s < _stages.size(); ++s) {
                auto& stage = _stages.at(s);
                
                // 衝突検知
                auto [isCollided, time] = CollisionDetection::testMove(
                    player, move,
                    stage, VGet(0, 0, 0)
                );
                // 衝突しているなら
                const float limitTime = _collisionStage.at(pid).first;
                if (isCollided && time < limitTime) {
                     _collisionStage.at(pid) = std::make_pair(time, s);
                }
            }
        }
    }

    void Physics::checkCollisionPlayer(const std::vector<AABB>& playerAABB) {
        for (int i = 0; i < _playerNum - 1; ++i) {
            for (int j = i + 1; j < _playerNum; ++j) {
                // 衝突検知
                auto [isCollided, time] = CollisionDetection::testMove(
                    playerAABB.at(i), _moves.at(i),
                    playerAABB.at(j), _moves.at(j)
                );
                if (isCollided) {
                    // 壁にぶつかるまえなら衝突情報を追加
                    const float timeLimit = min(_collisionStage.at(i).first, _collisionStage.at(j).first);
                    if (time < timeLimit) {
                        _collisionPlayer.at(i).at(j) = time;
                        _collisionPlayer.at(j).at(i) = time;
                    }
                }
            }
        }
    }
    std::vector<VECTOR> Physics::generateActualMove() const {
        std::vector<VECTOR> actualMoves(_playerNum);

        for (int pid = 0; pid < _playerNum; ++pid) {
            // 動き切る前にステージに衝突する場合
            if (isCollidedStage(pid)) {
                const float time = _collisionStage.at(pid).first;
                actualMoves.at(pid) = VScale(_moves.at(pid), time);
            }
            else {
                actualMoves.at(pid) = _moves.at(pid);
            }
        }
        return actualMoves;
    }

    void Physics::responseActualMove() {
        auto actualMoves = generateActualMove();
        MessageGenerator mg;
        mg.setSignature("move");
        mg.addArgument(0);
        mg.addArgument(0);
        mg.addArgument(0);

        for (int i = 0; i < _playerNum; ++i) {
            mg.setDestination("player", i);
            mg.updateArgument(0, actualMoves.at(i).x);
            mg.updateArgument(1, actualMoves.at(i).y);
            mg.updateArgument(2, actualMoves.at(i).z);
            send(mg.generate());
        }
    }

    void Physics::responseCheckCollision(int playerId1, int playerId2) {
        if (isCollided(playerId1, playerId2)) {
            MessageGenerator mg;
            mg.setDestination("Game", 0);
            mg.setSignature("collision");
            mg.addArgument(playerId1);
            mg.addArgument(playerId2);
            send(mg.generate());
        }
    }
}
