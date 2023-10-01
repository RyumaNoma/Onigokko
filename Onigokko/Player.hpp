#pragma once

namespace game {
	/**
	 * @brief インゲームのプレイヤークラス。
	 */
	class Player {
	public:
		enum class STATUS {
			NONE,
			ONI,
			PERSON
		};
		Player() = delete;

		/**
		 * @brief コンストラクタ。
		 * 
		 * @param oniSpeed 鬼状態の速度
		 * @param personSpeed 人間状態のそ度
		 */
		Player(float oniSpeed, float personSpeed);

		/**
		 * @brief 鬼になる。
		 */
		void beOni();

		/**
		 * @brief 人間になる。
		 */
		void bePerson();

		STATUS getStatus() const { return _status; }
		float getSpeed() const;
	private:
		STATUS _status;
		const float _OniSpeed;
		const float _PersonSpeed;
	};
}
