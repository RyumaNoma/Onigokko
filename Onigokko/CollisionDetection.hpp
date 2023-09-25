#pragma once
#include "DxLib.h"

namespace game {
	class AABB;

	/**
	 * @brief 衝突検出用関数群。
	 */
	class CollisionDetection {
	public:
		/**
		 * @brief 静止状態のAABB同士の衝突検出。
		 * 
		 * @param aabb1 静止状態のAABB
		 * @param aabb2 静止状態のAABB
		 * @return 衝突しているならtrue
		 */
		static bool testStop(const AABB& aabb1, const AABB& aabb2);

		/**
		 * @brief 運動状態のAABB同士の衝突検出。
		 * 
		 * @param aabb1 運動状態のAABB
		 * @param velocity1 aabb1の速度ベクトル
		 * @param aabb2 運動状態のAABB
		 * @param velocity2 aabb2の速度ベクトル
		 * @return 衝突しているならtrue
		 */
		static bool testMove(
			const AABB& aabb1, VECTOR velocity1,
			const AABB& aabb2, VECTOR velocity2
		);
		/**
		 * @brief ベクトル形式の線分と静止状態のAABBの衝突検出。
		 * 
		 * @param origin 線分の始点
		 * @param dir 線分のベクトル
		 * @param aabb 静止状態のAABB
		 * @return  衝突しているならtrue
		 */
		static bool testVectorAndAABB(const VECTOR origin, const VECTOR dir, const AABB& aabb);
	};
}
