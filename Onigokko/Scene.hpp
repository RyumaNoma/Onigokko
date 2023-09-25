#pragma once
#include <memory>
#include "MessageCommunicator.hpp"

namespace game {
	class Scene
		: public MessageCommunicator {
	public:
		Scene(MessageManagerPtr messageManager) : MessageCommunicator(messageManager) {}

		virtual ~Scene() {}

		/**
		 * @brief �`��֐��B
		 */
		virtual void draw() const = 0;

		/**
		 * @brief �X�V�֐��B
		 */
		virtual void update() = 0;
	};
	using ScenePtr = std::shared_ptr<Scene>;
	using SceneRef = std::shared_ptr<const Scene>;
}

