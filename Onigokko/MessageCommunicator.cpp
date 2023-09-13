#include "MessageCommunicator.hpp"
#include "MessageManager.hpp"

namespace game {
	MessageCommunicator::MessageCommunicator(MessageManagerPtr messageManager)
		: _messageManager(messageManager)
		, _tag()
		, _id()
	{}

	void MessageCommunicator::raiseHand(std::string tag) {
		_tag = tag;
		_id = _messageManager->setCommunicator(tag, shared_from_this());
	}
}
