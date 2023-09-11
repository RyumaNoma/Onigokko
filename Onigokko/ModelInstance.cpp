#include "ModelInstance.hpp"
#include "ModelResource.hpp"
#include "VectorOperator.hpp"
#include <stdexcept>
#include <fstream>

std::ostream& operator << (std::ostream& os, const DxLib::MATRIX& mat) {
	os << "(" << mat.m[0][0] << "," << mat.m[0][1] << "," << mat.m[0][2] << "," << mat.m[0][3] << ")" << std::endl
		<< "(" << mat.m[1][0] << "," << mat.m[1][1] << "," << mat.m[1][2] << "," << mat.m[1][3] << ")" << std::endl
		<< "(" << mat.m[2][0] << "," << mat.m[2][1] << "," << mat.m[2][2] << "," << mat.m[2][3] << ")" << std::endl
		<< "(" << mat.m[3][0] << "," << mat.m[3][1] << "," << mat.m[3][2] << "," << mat.m[3][3] << ")" << std::endl;
	return os;
}

namespace game {
	ModelInstance::ModelInstance(ModelResourceRef modelResource)
		: _scale(VGet(1.0f, 1.0f, 1.0f))
		, _translate(VGet(0.0f, 0.0f, 0.0f))
		, _angle(0.0f)
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
			worldVertexBuffer[i].pos = VTransform(worldVertexBuffer[i].pos, worldMatrix);
		}
		DrawPolygonIndexed3D(worldVertexBuffer, vertexNum, _modelResource->getIndexBuffer(), polygonNum, DX_NONE_GRAPH, false);
		const auto black = GetColor(0, 0, 0);
		const auto white = GetColor(255, 255, 255);
		DrawLine3D(VGet(0,0,0), VGet(100,0,0), white);
		DrawLine3D(VGet(100,0,0), VGet(100,100,0), white);
		DrawLine3D(VGet(100,100,0), VGet(0,100,0), white);
		DrawLine3D(VGet(0,100,0), VGet(0,0,0), white);
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
		_translate += difference;
	}

	void ModelInstance::moveTo(VECTOR destination) {
		_translate = destination;
	}

	void ModelInstance::setAngle(float rad) {
		_angle = rad;
	}

	void ModelInstance::rotate(float rotation) {
		_angle += rotation;
	}

	MATRIX ModelInstance::generateWorldMatrix() const {
		std::ofstream dbg("Debug.txt");
		// 回転
		MATRIX worldMatrix = MGetRotY(_angle);

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
		worldMatrix.m[3][0] = _translate.x;
		worldMatrix.m[3][1] = _translate.y;
		worldMatrix.m[3][2] = _translate.z;

		dbg.close();
		return worldMatrix;
	}
}
