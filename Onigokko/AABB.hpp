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

		void drawFrame() const;

		float getMinX() const { return _minX; }
		float getMaxX() const { return _maxX; }
		float getMinY() const { return _minY; }
		float getMaxY() const { return _maxY; }
		float getMinZ() const { return _minZ; }
		float getMaxZ() const { return _maxZ; }
	private:
		float _minX, _maxX;
		float _minY, _maxY;
		float _minZ, _maxZ;
	};
}
