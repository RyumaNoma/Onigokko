#pragma once
#include <memory>
#include "DxLib.h"

namespace game {
	class ModelInstance;
	using ModelInstanceRef = std::shared_ptr<const ModelInstance>;

	/**
	 * @brief AABB(axis-aligned bounding boxes)
	 */
	class AABB {
	public:
		AABB();

		void update(ModelInstanceRef model);

		void update(VECTOR min, VECTOR max);

		bool intersect(const AABB& aabb) const;

		void drawFrame() const;

		float getMinX() const { return minX; }
		float getMaxX() const { return maxX; }
		float getMinY() const { return minY; }
		float getMaxY() const { return maxY; }
		float getMinZ() const { return minZ; }
		float getMaxZ() const { return maxZ; }
	private:
		float minX, maxX;
		float minY, maxY;
		float minZ, maxZ;
	};
}
