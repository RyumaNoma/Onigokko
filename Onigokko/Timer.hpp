#pragma once
#include <memory>

namespace game {
	class Clock;
	using ClockRef = std::shared_ptr<const Clock>;

	/**
	 * @brief Clockクラスをもとに時間計測を行うクラス。
	 */
	class Timer {
	public:
		Timer() = delete;
		/**
		 * @brief コンストラクタ。
		 * @brief 時間計測を開始する。
		 * 
		 * @param clock もとにする時刻
		 */
		Timer(ClockRef clock);

		/**
		 * @brief 時間計測を開始する。
		 * 
		 */
		void start();

		/**
		 * @brief 前回のstart()からの経過時間を取得する。
		 * 
		 * @return  経過時間
		 */
		size_t getElapsed() const;
	private:
		ClockRef _clock;
		size_t _start;
	};
	using TimerPtr = std::shared_ptr<Timer>;
	using TimerRef = std::shared_ptr<const Timer>;
}

