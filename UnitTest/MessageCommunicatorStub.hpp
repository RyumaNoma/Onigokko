#pragma once
#include "MessageCommunicator.hpp"
#include <vector>
#include <string>

namespace game {
	class Enemy : public MessageCommunicator {
	public:
		Enemy(MessageManagerPtr mm) : MessageCommunicator(mm) {}
		void receive(const std::string& message) override;
		const std::vector<std::string>& getReceivedMessages() const { return _receivedMessages; }
		const std::string& getReceivedMessage(int index) const { return _receivedMessages.at(index); }
	private:
		std::vector<std::string> _receivedMessages;
	};

	class GameObject : public MessageCommunicator {
	public:
		GameObject(MessageManagerPtr mm) : MessageCommunicator(mm) {}
		void receive(const std::string& message) override;
		const std::vector<std::string>& getReceivedMessages() const { return _receivedMessages; }
		const std::string& getReceivedMessage(int index) const { return _receivedMessages.at(index); }
	private:
		std::vector<std::string> _receivedMessages;
	};
}