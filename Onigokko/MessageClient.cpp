#include "MessageClient.hpp"
#include "MessageServer.hpp"

namespace game {
	MessageClient::MessageClient(MessageServerPtr MessageServer)
		: _MessageServer(MessageServer)
		, _tag()
		, _id()
	{}

	void MessageClient::raiseHand(std::string tag) {
		_tag = tag;
		_id = _MessageServer->setCommunicator(tag, shared_from_this());
	}

	void MessageClient::send(const std::string& message) {
		_MessageServer->receive(message);
	}
}
