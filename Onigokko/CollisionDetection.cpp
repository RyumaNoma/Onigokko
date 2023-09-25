#include "CollisionDetection.hpp"
#include "AABB.hpp"

namespace game {
	bool CollisionDetection::testStop(const AABB& aabb1, const AABB& aabb2) {
		const bool collisionX = (aabb1.getMaxX() > aabb2.getMinX()) && (aabb1.getMinX() < aabb2.getMaxX());
		const bool collisionY = (aabb1.getMaxY() > aabb2.getMinY()) && (aabb1.getMinY() < aabb2.getMaxY());
		const bool collisionZ = (aabb1.getMaxZ() > aabb2.getMinZ()) && (aabb1.getMinZ() < aabb2.getMaxZ());
		return (collisionX && collisionY && collisionZ);
	}
}
