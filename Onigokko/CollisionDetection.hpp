#pragma once

namespace game {
	class AABB;

	/**
	 * @brief 衝突検出用関数群。
	 */
	class CollisionDetection {
	public:
		static bool testStop(const AABB& aabb1, const AABB& aabb2);
	};
}
