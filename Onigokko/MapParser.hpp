#pragma once
#include <string>
#include <unordered_map>
#include <memory>

namespace game {
	class MapParser {
	public:
		MapParser() = delete;
		
		/**
		 * @brief コンストラクタ。
		 * 
		 * @param filepath パースするファイル
		 */
		MapParser(const std::string& filepath);

		/**
		 * @brief キーが存在するかどうか。
		 * 
		 * @param key 確認するキー
		 * @return  存在するならtrue
		 */
		bool isExist(const std::string& key);

		/**
		 * @brief バリューを文字列として取得する。
		 * 
		 * @param key キー
		 * @param defaultValue キーが存在しない場合の値
		 * @return  バリュー
		 */
		std::string getAsString(const std::string& key, const char* defaultValue = "") const;

		/**
		 * @brief バリューを整数として取得する。
		 *
		 * @param key キー
		 * @param defaultValue キーが存在しない場合の値
		 * @return  バリュー
		 */
		int getAsInteger(const std::string& key, int defaultValue = 0) const;

		/**
		 * @brief バリューを浮動小数点数として取得する。
		 *
		 * @param key キー
		 * @param defaultValue キーが存在しない場合の値
		 * @return  バリュー
		 */
		float getAsFloat(const std::string& key, float defaultValue = 0.0f) const;
	private:
		std::unordered_map<std::string, std::string> _map;
	};
	using MapParserPtr = std::shared_ptr<MapParser>;
	using MapParserRef = std::shared_ptr<const MapParser>;
}
