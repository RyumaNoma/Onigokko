#pragma once
#include "MessageClient.hpp"
#include <vector>
#include <string>

namespace game {
	class MessageClientStub1 : public MessageClient {
	public:
		MessageClientStub1(MessageServerPtr mm) : MessageClient(mm) {}
		void receive(const std::string& message) override;
		const std::vector<std::string>& getReceivedMessages() const { return _receivedMessages; }
		const std::string& getReceivedMessage(int index) const { return _receivedMessages.at(index); }
	private:
		std::vector<std::string> _receivedMessages;
	};

	class MessageClientStub2 : public MessageClient {
	public:
		MessageClientStub2(MessageServerPtr mm) : MessageClient(mm) {}
		void receive(const std::string& message) override;
		const std::vector<std::string>& getReceivedMessages() const { return _receivedMessages; }
		const std::string& getReceivedMessage(int index) const { return _receivedMessages.at(index); }
	private:
		std::vector<std::string> _receivedMessages;
	};
}