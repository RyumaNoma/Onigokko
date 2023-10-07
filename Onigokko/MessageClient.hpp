#pragma once
#include <string>
#include <memory>

namespace game {
	class MessageServer;
	using MessageServerPtr = std::shared_ptr<MessageServer>;

	/**
	 * @brief メッセージ送受信者用インタフェース。
	 */
	class MessageClient
		: public std::enable_shared_from_this<MessageClient> {
	public:
		MessageClient() = delete;

		/**
		 * コンストラクタ。
		 * 
		 * @param MessageServer 送受信相手となるMessageServer
		 */
		MessageClient(MessageServerPtr MessageServer);

		virtual ~MessageClient() {}
		
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

		void send(const std::string& message);

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
		 MessageServerPtr _MessageServer;
		 std::string _tag;
		 int _id;
	};
	using MessageClientPtr = std::shared_ptr<MessageClient>;
	using MessageClientRef = std::shared_ptr<const MessageClient>;
}