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
		float getSpeed() const { return _speed; }
	private:
		STATUS _status;
		float _speed;
		const float _oniSpeed;
		const float _personSpeed;
	};
}
