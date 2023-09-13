#include "ModelInstance.hpp"
#include "ModelResource.hpp"
#include "VectorOperator.hpp"
#include <stdexcept>
#include <fstream>

namespace game {
	ModelInstance::ModelInstance(ModelResourceRef modelResource)
		: _scale(VGet(1.0f, 1.0f, 1.0f))
		, _position(VGet(0.0f, 0.0f, 0.0f))
		, _rotation(0.0f)
		, _anchorPosition(VGet(0.0f, 0.0f, 0.0f))
		, _modelResource(modelResource)
	{}

	void ModelInstance::draw() const {
		const MATRIX worldMatrix = generateWorldMatrix();

		const int vertexNum = _modelResource->getVertexNum();
		const int polygonNum = _modelResource->getPolygonNum();
		VERTEX3D* worldVertexBuffer = new VERTEX3D[vertexNum];

		std::copy(_modelResource->getVertexBuffer(), _modelResource->getVertexBuffer() + vertexNum,
			worldVertexBuffer);

		for (int i = 0; i < vertexNum; ++i) {
			worldVertexBuffer[i].pos = VSub(worldVertexBuffer[i].pos, _anchorPosition);
			worldVertexBuffer[i].pos = VTransform(worldVertexBuffer[i].pos, worldMatrix);
		}
		DrawPolygonIndexed3D(worldVertexBuffer, vertexNum, _modelResource->getIndexBuffer(), polygonNum, DX_NONE_GRAPH, false);
	}

	void ModelInstance::setScaleX(float scale) {
		if (scale <= 0.0f) { throw std::invalid_argument("x scale must plus"); }
		_scale.x = scale;
	}

	void ModelInstance::setScaleY(float scale) {
		if (scale <= 0.0f) { throw std::invalid_argument("y scale must plus"); }
		_scale.y = scale;
	}

	void ModelInstance::setScaleZ(float scale) {
		if (scale <= 0.0f) { throw std::invalid_argument("z scale must plus"); }
		_scale.z = scale;
	}

	void ModelInstance::setScale(float scale) {
		setScaleX(scale);
		setScaleY(scale);
		setScaleZ(scale);
	}

	void ModelInstance::setScale(VECTOR scale) {
		setScaleX(scale.x);
		setScaleY(scale.y);
		setScaleZ(scale.z);
	}

	void ModelInstance::move(VECTOR difference) {
		_position += difference;
	}

	void ModelInstance::moveTo(VECTOR destination) {
		_position = destination;
	}

	void ModelInstance::setRotation(float rotation) {
		_rotation = rotation;
	}

	void ModelInstance::rotate(float rotation) {
		_rotation += rotation;
	}

	void ModelInstance::setAnchor(VECTOR anchorPosition) {
		_anchorPosition = anchorPosition;
	}

	void ModelInstance::changeModelResource(ModelResourceRef newModelResource) {
		_modelResource = newModelResource;
	}

	MATRIX ModelInstance::generateWorldMatrix() const {
		// 回転
		MATRIX worldMatrix = MGetRotY(_rotation);

		// スケール
		worldMatrix.m[0][0] *= _scale.x;
		worldMatrix.m[0][1] *= _scale.x;
		worldMatrix.m[0][2] *= _scale.x;
		worldMatrix.m[1][0] *= _scale.y;
		worldMatrix.m[1][1] *= _scale.y;
		worldMatrix.m[1][2] *= _scale.y;
		worldMatrix.m[2][0] *= _scale.z;
		worldMatrix.m[2][1] *= _scale.z;
		worldMatrix.m[2][2] *= _scale.z;

		// 平行移動
		worldMatrix.m[3][0] = _position.x;
		worldMatrix.m[3][1] = _position.y;
		worldMatrix.m[3][2] = _position.z;

		return worldMatrix;
	}
}
