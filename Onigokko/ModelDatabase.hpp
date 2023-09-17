#pragma once
#include <unordered_map>
#include <string>
#include <memory>

namespace game {
	class ModelResource;
	using ModelResourcePtr = std::shared_ptr<ModelResource>;

	class ModelDatabase {
	public:
		/**
		 * @brief デフォルトコンストラクタ。
		 * 
		 */
		ModelDatabase();

		/**
		 * @brief ファイルをロードする。
		 * 同じファイル名の場合、リロードする。
		 * 
		 * @param filename ファイル名
		 */
		void load(const std::string& filename);

		/**
		 * @brief ファイル名をキーとしてモデルリソースを返す。
		 * @brief ロードされていない場合ロードを行う。
		 * 
		 * @param filename ファイル名
		 * @return  モデルリソース
		 */
		ModelResourcePtr fetch(const std::string& filename);

		/**
		 * @brief 既にロードされたモデルの数の取得。
		 * 
		 * @return 既にロードされたモデルの数
		 */
		size_t getSize() const { return _resources.size(); }
	private:
		std::unordered_map<std::string, ModelResourcePtr> _resources;
	};
	using ModelDatabasePtr = std::shared_ptr<ModelDatabase>;
}