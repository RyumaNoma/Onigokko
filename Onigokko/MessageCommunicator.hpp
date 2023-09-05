#pragma once
#include <string>
#include <memory>

namespace game {
	class MessageManager;
	using MessageManagerPtr = std::shared_ptr<MessageManager>;

	/**
	 * @brief メッセージ送受信者用インタフェース。
	 */
	class MessageCommunicator {
	public:
		MessageCommunicator() = delete;

		/**
		 * コンストラクタ。
		 * 
		 * @param messageManager 送受信相手となるMessageManager
		 */
		MessageCommunicator(MessageManagerPtr messageManager) : _messageManager(messageManager) {}
		virtual ~MessageCommunicator() {}
		
		/**
		 * メッセージを受け取る。
		 * 
		 * @param message メッセージマネージャーから送られてきたメッセージ
		 */
		virtual void receive(const std::string& message) = 0;
	protected:
		 MessageManagerPtr _messageManager;
	};
	using MessageCommunicatorPtr = std::shared_ptr<MessageCommunicator>;
}