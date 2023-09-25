#pragma once
#include <vector>
#include <string>
#include <sstream>

namespace game {
	/**
	 * @brief メッセージ生成用クラス。
	 */
	class MessageGenerator
	{
	public:
		/**
		 * コンストラクタ。
		 */
		MessageGenerator();

		/**
		 * 既に設定された項目からメッセージを生成する。
		 * 
		 * @return  生成されたメッセージ
		 */
		std::string generate() const;

		/**
		 * 宛先の設定。
		 * 
		 * @param destination 宛先タグ
		 * @param id 宛先タグ内のId
		 */
		void setDestination(const std::string& destination, int id);

		/**
		 * ブロードキャスト送信を行う際に設定する。
		 * 
		 * @param destination 宛先タグ
		 */
		void setDestinationBroadcast(const std::string& destination);

		/**
		 * 命令を設定する。
		 * 許可されている文字は、アルファベット・数字・ハイフン・アンダー・スコア・ピリオドのみ。
		 * 
		 * @param signature 命令
		 */
		void setSignature(const std::string& signature);

		/**
		 * 引数を一つ追加する。
		 * 出力演算子が定義されている必要あり。
		 * 
		 * @tparam ArgType 引数の型
		 * @param argument 引数
		 */
		template<class ArgType>
		void addArgument(const ArgType& argument);

		/**
		 * 既に追加されている引数を更新する。
		 * 引数の型が変わっても良い
		 * 出力演算子が定義されている必要アリ。
		 * 
		 * @tparam ArgType 引数の型
		 * @param index 引数の序数(0-indexed)
		 * @param newArgument 新しい引数の値
		 */
		template<class ArgType>
		void updateArgument(int index, const ArgType& newArgument);

		/**
		 * ブロードキャストかどうか。
		 * 
		 * @return  ブロードキャストならtrue、それ以外ならfalse
		 */
		bool isBroadcast() const;

		/**
		 * 宛先Idの取得。
		 * 
		 * @return  宛先Id
		 */
		int getDestinationId() const { return _destRange; }

		/**
		 * シグネチャの取得。
		 * 
		 * @return  シグネチャ
		 */
		const std::string& getSignature() const { return _signature; }

		/**
		 * 指定した引数の取得。
		 * 
		 * @param index 引数の序数(0-indexed)
		 * @return  引数
		 */
		const std::string& getArgument(int index) const { return _arguments.at(index); }

		/**
		 * 全ての引数の取得。
		 * 
		 * @return  全ての引数
		 */
		const std::vector<std::string>& getArguments() const { return _arguments; }
	private:
		bool isValidSignatureCharacter(char c) const;
	private:
		std::string _destTag;
		int _destRange;
		std::string _signature;
		std::vector<std::string> _arguments;
	};
	using MessageGeneratorPtr = std::shared_ptr<MessageGenerator>;
	using MessageGeneratorRef = std::shared_ptr<const MessageGenerator>;

	template<class ArgType>
	inline void MessageGenerator::addArgument(const ArgType& argument) {
		std::ostringstream oss;
		oss << argument;

		_arguments.emplace_back(oss.str());
	}

	template<class ArgType>
	inline void MessageGenerator::updateArgument(int index, const ArgType& newArgument) {
		std::ostringstream oss;
		oss << newArgument;

		_arguments.at(index) = oss.str();
	}
}