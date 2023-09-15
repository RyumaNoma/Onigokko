#pragma once
#include <memory>

namespace game {
	/**
	 * @brief フレーム数に準拠した時間管理クラス。
	 * @attention フレーム数がsize_tの範囲を超えることはないものとして実装する
	 */
	class Clock {
	public:
		/**
		 * @brief コンストラクタ。時刻0で初期化される
		 */
		Clock();

		/**
		 * @brief 時刻を1進める。
		 * 
		 */
		void countUp();

		/**
		 * @brief 現在の時刻を取得する。
		 * 
		 * @return  現在の時刻
		 */
		size_t now() const { return _now; }
	private:
		size_t _now;
	};
	using ClockRef = std::shared_ptr<const Clock>;
	using ClockPtr = std::shared_ptr<Clock>;
}
