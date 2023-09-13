#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

namespace game {
	class MessageCommunicator;
	using MessageCommunicatorPtr = std::shared_ptr<MessageCommunicator>;

	/**
	 * @brief メッセージの送受信を管理する。
	 */
	class MessageManager {
		using TagCommunicators = std::unordered_map<int, MessageCommunicatorPtr>;
		using CommunicatorHierarchy = 
			std::unordered_map<std::string, TagCommunicators>;
	public:
		/**
		 * コンストラクタ。
		 */
		MessageManager();

		/**
		 * @brief メッセージ送受信者として(タグ)に紐づける。
		 * @brief Idは自動的に割り当てられる。
		 * @brief メッセージ受け取り意思表明となる。
		 * 
		 * @param tag 受け取りタグ
		 * @param communicator メッセージ送受信者
		 * @return Id
		 */
		int setCommunicator(const std::string& tag, MessageCommunicatorPtr communicator);

		/**
		 * 設定されたメッセージ送受信者の紐づけを解除する。
		 * 
		 * @param tag 受け取りタグ
		 * @param id Id
		 */
		void eraseCommunicator(const std::string& tag, int id);

		/**
		 * メッセージの受け取り。
		 * メッセージのパースは行わない
		 * 
		 * @param message メッセージ
		 */
		void receive(const std::string& message);

		/**
		 * 受け取ったメッセージを全て送信。
		 * メッセージのパースはここで行う。
		 * 
		 */
		void sendAll();

		/**
		 * 受け取ったがまだ送信していないメッセージの参照を取得する。
		 * 
		 * @return  受け取ったがまだ送信していないメッセージ
		 */
		const std::vector<std::string>& getMessages() const { return _messages; }

		/**
		 * メッセージ送受信者の階層構造の参照を取得する。
		 * 
		 * @return  メッセージ送受信者の階層構造の参照
		 */
		const CommunicatorHierarchy& getCommunicators() const { return _communicators; }

		/**
		 * メッセージ送受信者の取得。
		 * 
		 * @param tag タグ
		 * @param id Id
		 * @return  メッセージ送受信者（無ければnullptr）
		 */
		MessageCommunicatorPtr getCommunicator(const std::string& tag, int id) const;
	private:
		void sendBroadcast(const std::string& tag, const std::string& messageBody);
		
		int useNextId(const std::string& tag);
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
		std::unordered_map<std::string, int> _nextIds;
	};
	using MessageManagerPtr = std::shared_ptr<MessageManager>;
}