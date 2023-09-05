#include "pch.h"
#include "MessageCommunicatorStub.hpp"

namespace game {
	void Enemy::receive(const std::string& message) {
		_receivedMessages.push_back(message);
	}

	void GameObject::receive(const std::string& message) {
		_receivedMessages.push_back(message);
	}
}