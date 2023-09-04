#pragma once
#include <string>
#include <memory>

namespace game {
	class MessageManager;

	class MessageCommunicator {
		using MessageManagerPtr = std::shared_ptr<MessageManager>;
	public:
		MessageCommunicator() = delete;
		MessageCommunicator(MessageManagerPtr messageManager) : _messageManager(messageManager) {}
		virtual ~MessageCommunicator() {}

		virtual void send(const std::string& message) = 0;
		virtual void receive(const std::string& message) = 0;
	protected:
		 MessageManagerPtr _messageManager;
	};
}