#pragma once
#include <memory>
#include <vector>
#include "DxLib.h"
#include "MessageClient.hpp"

namespace game {
	class ModelDatabase;
	using ModelDatabasePtr = std::shared_ptr<ModelDatabase>;

	class ModelInstance;
	using ModelInstancePtr = std::shared_ptr<ModelInstance>;
	using ModelInstanceRef = std::shared_ptr<const ModelInstance>;

	/**
	 * @brief ゲーム内のステージを管理する。
	 */
	class StageModel
		: public MessageClient
	{
	public:
		/**
		 * @brief コンストラクタ。
		 * @brief 床と壁4枚が生成される。
		 * 
		 * @param scale ステージの大きさ
		 * @param floorFilename 床のモデルファイル
		 * @param wallFilename 壁のモデルファイル
		 */
		StageModel(MessageServerPtr server, VECTOR scale, const std::string& floorFilename, const std::string& wallFilename);

		/**
		 * @brief モデルDBを通したステージの生成。
		 * @brief 床と壁4枚が生成される。
		 * 
		 * @param modelDatabase 元となるモデルDB
		 * @param scale ステージの大きさ
		 * @param floorFilename 床のモデルファイル
		 * @param wallFilename 壁のモデルファイル
		 */
		StageModel(MessageServerPtr server, ModelDatabasePtr modelDatabase, VECTOR scale, const std::string& floorFilename, const std::string& wallFilename);

		void receive(const std::string& message) override;

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
		void generate(const std::string& floorFilename, const std::string& wallFilename);
		void generate(ModelDatabasePtr modelDatabase, const std::string& floorFilename, const std::string& wallFilename);
		void init(VECTOR scale);

		ModelInstancePtr _floor;
		std::vector<ModelInstancePtr> _walls;
	};
	using StageModelPtr = std::shared_ptr<StageModel>;
	using StageModelRef = std::shared_ptr<const StageModel>;
}
