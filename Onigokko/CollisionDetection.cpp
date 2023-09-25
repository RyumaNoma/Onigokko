#include "CollisionDetection.hpp"
#include "AABB.hpp"
#include "VectorOperator.hpp"
#include <fstream>

namespace game {
	bool CollisionDetection::testStop(const AABB& aabb1, const AABB& aabb2) {
		const bool collisionX = (aabb1.getMaxX() > aabb2.getMinX()) && (aabb1.getMinX() < aabb2.getMaxX());
		const bool collisionY = (aabb1.getMaxY() > aabb2.getMinY()) && (aabb1.getMinY() < aabb2.getMaxY());
		const bool collisionZ = (aabb1.getMaxZ() > aabb2.getMinZ()) && (aabb1.getMinZ() < aabb2.getMaxZ());
		return (collisionX && collisionY && collisionZ);
	}
	bool CollisionDetection::testMove(
		const AABB& aabb1, VECTOR velocity1,
		const AABB& aabb2, VECTOR velocity2
	) {
		// 静止状態の場合
		if (isZero(velocity1) && isZero(velocity2)) {
			return testStop(aabb1, aabb2);
		}
		// 相対速度
		const VECTOR relativeVelocity = velocity1 - velocity2;
		// aabb1を点として扱い、aabb2を拡張する
		const VECTOR point = VGet(aabb1.getMinX(), aabb1.getMinY(), aabb1.getMinZ());
		AABB exaabb;
		VECTOR exMin, exMax;
		exMin.x = aabb2.getMinX() - (aabb1.getMaxX() - aabb1.getMinX());
		exMin.y = aabb2.getMinY() - (aabb1.getMaxY() - aabb1.getMinY());
		exMin.z = aabb2.getMinZ() - (aabb1.getMaxZ() - aabb1.getMinZ());
		exMax.x = aabb2.getMaxX();
		exMax.y = aabb2.getMaxY();
		exMax.z = aabb2.getMaxZ();
		exaabb.update(exMin, exMax);
		
		return testVectorAndAABB(point, relativeVelocity, exaabb);
	}
	bool CollisionDetection::testVectorAndAABB(const VECTOR origin, const VECTOR dir, const AABB& aabb) {
		// x
		if (abs(dir.x) > FLT_EPSILON) {
			const float lineX = (dir.x > 0) ? aabb.getMinX() : aabb.getMaxX();
			const float time = (lineX - origin.x) / dir.x;

			if (time < 0.0f || time > 1.0f) { return false; }

			const float hitY = origin.y + time * dir.y;
			const float hitZ = origin.z + time * dir.z;
			if (aabb.getMinY() <= hitY && hitY <= aabb.getMaxY() &&
				aabb.getMinZ() <= hitZ && hitZ <= aabb.getMaxZ())
			{
				return true;
			}
		}
		// y
		if (abs(dir.y) > FLT_EPSILON) {
			const float lineY = (dir.y > 0) ? aabb.getMinY() : aabb.getMaxY();
			const float time = (lineY - origin.y) / dir.y;

			if (time < 0.0f || time > 1.0f) { return false; }

			const float hitX = origin.x + time * dir.x;
			const float hitZ = origin.z + time * dir.z;
			if (aabb.getMinY() <= hitX && hitX <= aabb.getMaxY() &&
				aabb.getMinZ() <= hitZ && hitZ <= aabb.getMaxZ())
			{
				return true;
			}
		}
		// z
		if (abs(dir.z) > FLT_EPSILON) {
			const float lineZ = (dir.z > 0) ? aabb.getMinZ() : aabb.getMaxZ();
			const float time = (lineZ - origin.z) / dir.z;

			if (time < 0.0f || time > 1.0f) { return false; }

			const float hitX = origin.x + time * dir.x;
			const float hitY = origin.y + time * dir.y;
			if (aabb.getMinX() <= hitX && hitX <= aabb.getMaxX() &&
				aabb.getMinY() <= hitY && hitY <= aabb.getMaxY())
			{
				return true;
			}
		}
		return false;
	}
}
