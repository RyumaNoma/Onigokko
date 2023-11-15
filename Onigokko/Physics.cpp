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
}
