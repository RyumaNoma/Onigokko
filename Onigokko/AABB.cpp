#include "AABB.hpp"
#include "ModelInstance.hpp"
#include "ModelResource.hpp"
#include <stdexcept>
#include <limits>

namespace game {
	AABB::AABB()
		: _minX(0.0f)
		, _maxX(1.0f)
		, _minY(0.0f)
		, _maxY(1.0f)
		, _minZ(0.0f)
		, _maxZ(1.0f)
	{}

	void AABB::update(ModelInstanceRef model) {
		const auto worldVertex = model->calcWorldVertex();
		const int vertexNum = model->getModelResource()->getVertexNum();
		const float INF = 1e9;
		// 初期化
		_minX = _minY = _minZ = INF;
		_maxX = _maxY = _maxZ = -INF;

		for (int i = 0; i < vertexNum; ++i) {
			_minX = min(_minX, worldVertex[i].x);
			_minY = min(_minY, worldVertex[i].y);
			_minZ = min(_minZ, worldVertex[i].z);
			_maxX = max(_maxX, worldVertex[i].x);
			_maxY = max(_maxY, worldVertex[i].y);
			_maxZ = max(_maxZ, worldVertex[i].z);
		}
	}

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

	void AABB::drawFrame() const {
		const auto red = GetColor(255, 0, 0);
		const VECTOR points[] = {
			VGet(_minX, _maxY, _minZ),
			VGet(_minX, _maxY, _maxZ),
			VGet(_maxX, _maxY, _maxZ),
			VGet(_maxX, _maxY, _minZ),
			VGet(_minX, _minY, _minZ),
			VGet(_minX, _minY, _maxZ),
			VGet(_maxX, _minY, _maxZ),
			VGet(_maxX, _minY, _minZ)
		};
		DrawLine3D(points[0], points[1], red);
		DrawLine3D(points[1], points[2], red);
		DrawLine3D(points[2], points[3], red);
		DrawLine3D(points[3], points[0], red);
		DrawLine3D(points[4], points[5], red);
		DrawLine3D(points[5], points[6], red);
		DrawLine3D(points[6], points[7], red);
		DrawLine3D(points[7], points[4], red);
		DrawLine3D(points[0], points[4], red);
		DrawLine3D(points[1], points[5], red);
		DrawLine3D(points[2], points[6], red);
		DrawLine3D(points[3], points[7], red);
	}
}
