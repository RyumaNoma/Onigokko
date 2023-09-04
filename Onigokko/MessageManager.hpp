#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

namespace game {
	class MessageCommunicator;
	using MessageCommunicatorPtr = std::shared_ptr<MessageCommunicator>;

	class MessageManager {
		using CommunicatorHierarchy = 
			std::unordered_map<std::string,
							   std::unordered_map<int,
												  std::vector<MessageCommunicatorPtr>>>;
	public:
		MessageManager();

		void setCommunicator(const std::string& tag, int id, MessageCommunicatorPtr communicator);
		void receive(const std::string& message);
		void sendAll();

		const std::vector<std::string>& getMessages() const { return _messages; }
		const CommunicatorHierarchy& getCommunicators() const { return _communicators; }

		// –³‚¯‚ê‚Înullptr‚ð•Ô‚·
		MessageCommunicatorPtr getCommunicator(const std::string& tag, int id) const;
	private:
		std::vector<std::string> _messages;
		/*
		ŽóMŽÒ‚ÌŠK‘w\‘¢
		tag -> id
		ex)
		- enemy
			- 0
			- 1
		- immutableObject
			- 0
			- 2
		*/
		CommunicatorHierarchy _communicators;
	};
	using MessageManagerPtr = std::shared_ptr<MessageManager>;
}