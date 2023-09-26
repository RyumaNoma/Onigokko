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
		const int vertexNum = _modelResource->getVertexNum();
		const int polygonNum = _modelResource->getPolygonNum();

		// モデルリソースの内容をコピー
		std::shared_ptr<VERTEX3D[]> worldVertexBuffer(new VERTEX3D[vertexNum]);
		copyFromModelResource(worldVertexBuffer);

		// ワールド座標系での座標を算出し代入
		const auto worldVertexPos = calcWorldVertex();
		for (int i = 0; i < vertexNum; ++i) {
			worldVertexBuffer[i].pos = worldVertexPos[i];
		}
		// 法線ベクトルのワールド変換
		const auto worldVertexNorm = calcWorldNorm();
		for (int i = 0; i < vertexNum; ++i) {
			worldVertexBuffer[i].norm = worldVertexNorm[i];
		}
		// 描画
		DrawPolygonIndexed3D(worldVertexBuffer.get(), vertexNum, _modelResource->getIndexBuffer(), polygonNum, DX_NONE_GRAPH, false);
	}

	std::vector<VECTOR> ModelInstance::calcWorldVertex() const {
		const int vertexNum = _modelResource->getVertexNum();
		VERTEX3D const* vertexBuffer = _modelResource->getVertexBuffer();
		std::vector<VECTOR> vertex(vertexNum);
		const MATRIX worldMatrix = generateWorldMatrix();

		// ワールド変換
		for (int i = 0; i < vertexNum; ++i) {
			vertex[i] = VTransform(VSub(vertexBuffer[i].pos, _anchorPosition), worldMatrix);
		}
		return vertex;
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

	MATRIX ModelInstance::generateWorldMatrixSR() const {
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

		return worldMatrix;
	}

	void ModelInstance::copyFromModelResource(std::shared_ptr<VERTEX3D[]> dst) const {
		const int vertexNum = _modelResource->getVertexNum();
		auto src = _modelResource->getVertexBuffer();
		for (int i = 0; i < vertexNum; ++i) {
			dst[i].dif = src[i].dif;
			dst[i].spc = src[i].spc;
			dst[i].u = src[i].u;
			dst[i].v = src[i].v;
		}
	}
	std::vector<VECTOR> ModelInstance::calcWorldNorm() const {
		const int vertexNum = _modelResource->getVertexNum();
		VERTEX3D const* vertexBuffer = _modelResource->getVertexBuffer();
		std::vector<VECTOR> vertex(vertexNum);
		// ワールド変換行列の逆転置行列
		const MATRIX worldMatrix = MTranspose(MInverse(generateWorldMatrixSR()));

		// ワールド変換
		for (int i = 0; i < vertexNum; ++i) {
			vertex[i] = VTransform(vertexBuffer[i].norm, worldMatrix);
		}
		return vertex;
	}
}
