#pragma once
#include "MessageClient.hpp"

namespace game {
	class InGameInputKeyboard
		: public MessageClient {
	public:
		InGameInputKeyboard(MessageServerPtr server);

		virtual void receive(const std::string& message) override;
	private:
		void responseMove() const;
		void responseGetSkillItem() const;
		void responseUseSkillItem() const;
	};
	using InGameInputKeyboardPtr = std::shared_ptr<InGameInputKeyboard>;
	using InGameInputKeyboardRef = std::shared_ptr<const InGameInputKeyboard>;
}
