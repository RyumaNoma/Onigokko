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
		 * @brief 描画関数。
		 */
		virtual void draw() const = 0;

		/**
		 * @brief 更新関数。
		 */
		virtual void update() = 0;
	};
	using ScenePtr = std::shared_ptr<Scene>;
	using SceneRef = std::shared_ptr<const Scene>;
}

