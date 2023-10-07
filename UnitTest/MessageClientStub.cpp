#include "pch.h"
#include "MessageClientStub.hpp"

namespace game {
	void MessageClientStub1::receive(const std::string& message) {
		_receivedMessages.push_back(message);
	}

	void MessageClientStub2::receive(const std::string& message) {
		_receivedMessages.push_back(message);
	}
}