#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

namespace game {
	class MessageCommunicator;
	using MessageCommunicatorPtr = std::shared_ptr<MessageCommunicator>;

	class MessageManager {
		using TagCommunicators = std::unordered_map<int, MessageCommunicatorPtr>;
		using CommunicatorHierarchy = 
			std::unordered_map<std::string, TagCommunicators>;
	public:
		MessageManager();

		void setCommunicator(const std::string& tag, int id, MessageCommunicatorPtr communicator);
		// TODO: テストと実装
		void eraseCommunicator(const std::string& tag, int id);
		void receive(const std::string& message);
		void sendAll();

		const std::vector<std::string>& getMessages() const { return _messages; }
		const CommunicatorHierarchy& getCommunicators() const { return _communicators; }

		// 無ければnullptrを返す
		MessageCommunicatorPtr getCommunicator(const std::string& tag, int id) const;
	private:
		void sendBroadcast(const std::string& tag, const std::string& messageBody);
	private:
		std::vector<std::string> _messages;
		/*
		受信者の階層構造
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