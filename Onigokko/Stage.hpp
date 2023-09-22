#pragma once
#include <memory>
#include <vector>

namespace DxLib {
	class VECTOR;
}

namespace game {
	class ModelDatabase;
	using ModelDatabaseRef = std::shared_ptr<const ModelDatabase>;

	class ModelInstance;
	using ModelInstancePtr = std::shared_ptr<ModelInstance>;
	using ModelInstanceRef = std::shared_ptr<const ModelInstance>;

	/**
	 * @brief ゲーム内のステージを管理する。
	 */
	class Stage {
	public:
		/**
		 * @brief コンストラクタ。
		 * @brief 床と壁4枚が生成される。
		 * 
		 * @param scale ステージの大きさ
		 */
		Stage(DxLib::VECTOR scale);

		/**
		 * @brief モデルDBを通したステージの生成。
		 * @brief 床と壁4枚が生成される。
		 * 
		 * @param modelDatabase 元となるモデルDB
		 * @param scale ステージの大きさ
		 */
		Stage(ModelDatabaseRef modelDatabase, DxLib::VECTOR scale);

		/**
		 * @brief ステージの持つ全てのオブジェクトの描画。
		 */
		void draw() const;

		/**
		 * @brief 床オブジェクトの取得。
		 * 
		 * @return  床オブジェクト
		 */
		ModelInstanceRef getFloor() const { return _floor; }

		/**
		 * @brief 壁オブジェクトの取得。
		 * 
		 * @return  壁オブジェクト
		 */
		std::vector<ModelInstanceRef> getWalls() const;

		/**
		 * @brief ステージの持つすべてのオブジェクトの取得。
		 * 
		 * @return  ステージの持つすべてのオブジェクト（床,壁0,壁1,壁2,壁3の順）
		 */
		std::vector<ModelInstanceRef> getAllObjects() const;
	private:
		/**
		 * @brief 床と壁4枚を生成する。
		 *
		 * @param scale ステージの大きさ
		 */
		void initStage(DxLib::VECTOR scale);

		ModelInstancePtr _floor;
		std::vector<ModelInstancePtr> _walls;
	};
}
