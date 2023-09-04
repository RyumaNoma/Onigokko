#pragma once
#include <string>
#include <memory>

namespace game {
	class MessageManager;
	using MessageManagerPtr = std::shared_ptr<MessageManager>;

	class MessageCommunicator {
	public:
		MessageCommunicator() = delete;
		MessageCommunicator(MessageManagerPtr messageManager) : _messageManager(messageManager) {}
		virtual ~MessageCommunicator() {}
		
		virtual void receive(const std::string& message) = 0;
	protected:
		 MessageManagerPtr _messageManager;
	};
	using MessageCommunicatorPtr = std::shared_ptr<MessageCommunicator>;
}