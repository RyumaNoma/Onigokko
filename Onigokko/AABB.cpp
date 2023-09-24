#include "AABB.hpp"

namespace game {
	AABB::AABB()
		: _minX(0.0f)
		, _maxX(1.0f)
		, _minY(0.0f)
		, _maxY(1.0f)
		, _minZ(0.0f)
		, _maxZ(1.0f)
	{}

	void AABB::update(VECTOR min, VECTOR max) {
		if (min.x > max.x) { throw std::invalid_argument("min.x > max.x"); }
		if (min.y > max.y) { throw std::invalid_argument("min.y > max.y"); }
		if (min.z > max.z) { throw std::invalid_argument("min.z > max.z"); }
		_minX = min.x;
		_minY = min.y;
		_minZ = min.z;
		_maxX = max.x;
		_maxY = max.y;
		_maxZ = max.z;
	}

}
