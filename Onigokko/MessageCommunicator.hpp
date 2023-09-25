#pragma once
#include <string>
#include <memory>

namespace game {
	class MessageManager;
	using MessageManagerPtr = std::shared_ptr<MessageManager>;

	/**
	 * @brief メッセージ送受信者用インタフェース。
	 */
	class MessageCommunicator
		: public std::enable_shared_from_this<MessageCommunicator> {
	public:
		MessageCommunicator() = delete;

		/**
		 * コンストラクタ。
		 * 
		 * @param messageManager 送受信相手となるMessageManager
		 */
		MessageCommunicator(MessageManagerPtr messageManager);

		virtual ~MessageCommunicator() {}
		
		/**
		 * メッセージを受け取る。
		 * 
		 * @param message メッセージマネージャーから送られてきたメッセージ
		 */
		virtual void receive(const std::string& message) = 0;

		/**
		 * @brief メッセージ受け取り意思表明をする。
		 * 
		 * @param tag 受け取りタグ
		 */
		void raiseHand(std::string tag);

		/**
		 * @brief 最後に受け取り意思表明をしたタグの取得。
		 * 
		 * @return  最後に受け取り意思表明をしたタグ
		 */
		const std::string& getTag() const { return _tag; }

		/**
		 * @brief 最後に受け取り意思表明をしたIdの取得。
		 *
		 * @return  最後に受け取り意思表明をしたId
		 */
		int getId() const { return _id; }
	protected:
		 MessageManagerPtr _messageManager;
		 std::string _tag;
		 int _id;
	};
	using MessageCommunicatorPtr = std::shared_ptr<MessageCommunicator>;
	using MessageCommunicatorRef = std::shared_ptr<const MessageCommunicator>;
}