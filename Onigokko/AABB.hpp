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

		/**
		 * @brief モデルインスタンスによるAABB更新。
		 * @brief 計算量はモデルの頂点数に比例する
		 * 
		 * @param model モデルインスタンス
		 */
		void update(ModelInstanceRef model);

		/**
		 * @brief 頂点minと頂点maxを対角線とする直方体をAABBとして直接設定する。
		 * @attention minとmaxの各x,y,zはmaxの方が大きくなければならない。
		 * 
		 * @param min 
		 * @param max 
		 */
		void update(VECTOR min, VECTOR max);

		/**
		 * @brief AABBを赤いフレームで描画する。
		 * 
		 */
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
