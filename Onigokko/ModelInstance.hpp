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
		 * @brief 注視点を向く。
		 * 
		 * @param fixation 注視点座標
		 */
		void lookAt(VECTOR fixation);

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
		VECTOR getTranslate() const { return _translate; }

		/**
		 * @brief 向きの取得。
		 * @attention デフォルトの向きは(0, 0, -1)とする
		 * 
		 * @return  向き
		 */
		VECTOR getRotate() const { return _rotate; }

		/**
		 * @brief 元となるモデルの取得。
		 * 
		 * @return  元となるモデル
		 */
		ModelResourceRef getModelResource() const { return _modelResource; }
	private:
		MATRIX generateScaleMatrix() const;
		MATRIX generateTranslateMatrix() const;
		MATRIX generateRotateMatrix() const;
		MATRIX generateInstanceMatrix() const;
	private:
		VECTOR _scale;
		VECTOR _translate;
		VECTOR _rotate;
		ModelResourceRef _modelResource;
	};
}