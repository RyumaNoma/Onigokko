#pragma once
#include "DxLib.h"
#include <memory>

namespace game {
	class ModelResource;
	using ModelResourceRef = std::shared_ptr<const ModelResource>;

	class ModelInstance {
	public:
		ModelInstance() = delete;

		/**
		 * @brief コンストラクタ。
		 * 
		 * @param modelResource 元となるモデル 
		 */
		ModelInstance(ModelResourceRef modelResource);

		ModelInstance(const ModelInstance& mi) = default;

		ModelInstance& operator= (const ModelInstance& mi) = default;

		/**
		 * @brief 描画の実行。
		 *
		 */
		void draw() const;

		/**
		 * @brief X方向への拡大縮小。
		 * 
		 * @param scale 拡大倍率
		 */
		void setScaleX(float scale);

		/**
		 * @brief Y方向への拡大縮小。
		 *
		 * @param scale 拡大倍率
		 */
		void setScaleY(float scale);

		/**
		 * @brief Z方向への拡大縮小。
		 *
		 * @param scale 拡大倍率
		 */
		void setScaleZ(float scale);

		/**
		 * @brief XYZ方向へ同じだけ拡大縮小する　。
		 *
		 * @param scale 拡大倍率
		 */
		void setScale(float scale);

		/**
		 * @brief XYZ方向それぞれの倍率を指定して拡大縮小する。
		 *
		 * @param scale 拡大倍率
		 */
		void setScale(VECTOR scale);

		/**
		 * @brief 指定した距離を移動する。
		 * 
		 * @param difference 移動量
		 */
		void move(VECTOR difference);
		
		/**
		 * @brief 指定した位置に移動する。
		 * 
		 * @param destination 目的地
		 */
		void moveTo(VECTOR destination);

		/**
		 * @brief モデルの向きを設定する。
		 * @brief Y軸を中心とした回転
		 * 
		 * @param rad 角度[単位：ラジアン]
		 */
		void setRotation(float rotation);

		/**
		 * @brief 指定した角度だけ回転する。
		 * 
		 * @param difference 回転する角度
		 */
		void rotate(float rotation);

		/**
		 * @brief XYZ方向の拡大倍率を取得する。
		 * 
		 * @return  拡大倍率
		 */
		VECTOR getScale() const { return _scale; }

		/**
		 * @brief 位置座標の取得。
		 * 
		 * @return  位置座標
		 */
		VECTOR getPosition() const { return _position; }

		/**
		 * @brief 向きの取得。
		 * 
		 * @return  向き[単位：ラジアン]
		 */
		float getRotation() const { return _rotation; }

		/**
		 * @brief 元となるモデルの取得。
		 * 
		 * @return  元となるモデル
		 */
		ModelResourceRef getModelResource() const { return _modelResource; }
	private:
		MATRIX generateWorldMatrix() const;
	private:
		VECTOR _scale;
		VECTOR _position;
		float _rotation;
		ModelResourceRef _modelResource;
	};
}