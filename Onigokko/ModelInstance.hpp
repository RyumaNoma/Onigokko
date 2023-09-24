﻿#pragma once
#include "DxLib.h"
#include <memory>
#include <vector>

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
		 * @brief 全頂点のワールド座標を計算する。
		 * 
		 * @return  全頂点のワールド座標
		 */
		std::vector<VECTOR> calcWorldVertex() const;

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
		 * @attention y軸マイナス方向を見て時計回りに回転する
		 * 
		 * @param difference 回転する角度
		 */
		void rotate(float rotation);

		/**
		 * @brief 基準点座標を設定する。
		 * @details 回転・スケール・平行移動の基準点となる。
		 * 
		 * @param anchorPosition 基準点座標
		 */
		void setAnchor(VECTOR anchorPosition);

		/**
		 * @brief 元となるモデルを変更する。
		 * 
		 * @param newModelResource 変更後の元となるモデル
		 */
		void changeModelResource(ModelResourceRef newModelResource);

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
		 * @brief 基準点座標の取得。
		 * @details 回転・スケール・平行移動の基準点となる。
		 * 
		 * @return  基準点座標
		 */
		VECTOR getAnchorPosition() const { return _anchorPosition; }

		/**
		 * @brief 元となるモデルの取得。
		 * 
		 * @return  元となるモデル
		 */
		ModelResourceRef getModelResource() const { return _modelResource; }
	private:
		MATRIX generateWorldMatrix() const;

		/**
		 * @brief モデルリソースの必要な頂点情報をコピーする。
		 * @brief 具体的にはnorm,dif,spc,u,vのみをコピーし、pos,su,svはコピーしない
		 * （posはワールド変換後、コピーするためここではコピーしない）
		 * @attention dstは頂点数分、領域を確保する必要あり
		 * 
		 * @param dst コピー先
		 */
		void copyFromModelResource(std::shared_ptr<VERTEX3D[]> dst) const;
	private:
		VECTOR _scale;
		VECTOR _position;
		float _rotation;
		VECTOR _anchorPosition;
		ModelResourceRef _modelResource;
	};
}