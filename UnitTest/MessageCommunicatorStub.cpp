#include "pch.h"
#include "MessageClientStub.hpp"

namespace game {
	void Enemy::receive(const std::string& message) {
		_receivedMessages.push_back(message);
	}

	void GameObject::receive(const std::string& message) {
		_receivedMessages.push_back(message);
	}
}