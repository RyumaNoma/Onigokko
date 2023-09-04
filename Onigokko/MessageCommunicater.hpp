#pragma once
#include <string>
#include <memory>

namespace game {
	class MessageManager;

	class MessageCommunicater {
	public:
		MessageCommunicater() {}
		virtual ~MessageCommunicater() {}

		virtual void send(const std::string& message) = 0;
		virtual void receive(const std::string& message) = 0;
	protected:
		std::shared_ptr<MessageManager> _messageManager;
	};
}