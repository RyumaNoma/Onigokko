#include "Physics.hpp"

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
}
