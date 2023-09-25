#pragma once
#include "InGameInputInterface.hpp"

namespace game {
	class InGameInputKeyboard
		: public InGameInputInterface {
	public:
		/**
		 * @brief WASDで8方向移動。
		 * 
		 * @return  移動方向
		 */
		virtual MOVE_DIRECTION move() override;

		/**
		 * @brief WASDで8方向移動。
		 * 
		 * @return  移動方向
		 */
		virtual Direction getDirection() override;

		/**
		 * @brief 右クリックでアイテム取得。
		 * 
		 * @return  アイテム取得ならtrue
		 */
		virtual bool getSkillItem() override;

		/**
		 * @brief 左クリックでアイテム使用。
		 * 
		 * @return  アイテム使用ならtrue
		 */
		virtual bool useSkillItem() override;
	private:
		Direction getDirectionWASD();
	};
	using InGameInputKeyboardPtr = std::shared_ptr<InGameInputKeyboard>;
	using InGameInputKeyboardRef = std::shared_ptr<const InGameInputKeyboard>;
}
