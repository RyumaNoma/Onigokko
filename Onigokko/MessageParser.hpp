#pragma once
#include <string>
#include <vector>
#include <memory>

namespace game {
	/**
	 * @brief メッセージパーサ。
	 */
	class MessageParser
	{
	public:
		MessageParser() = delete;

		/**
		 * コンストラクタ。パースを行う。
		 * 
		 * @param message パースするメッセージ
		 */
		MessageParser(const std::string& message);
		
		/**
		 * 宛先タグの取得。
		 * 
		 * @return  宛先タグ
		 */
		std::string getDestination() const { return _destTag; }

		/**
		 * ブロードキャストかどうか。
		 * 
		 * @return ブロードキャストならtrue、それ以外ならfalse
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
		std::string getSignature() const { return _signature; }

		/**
		 * 指定した引数を文字列として取得する。
		 * 
		 * @param index 引数の序数(0-indexed)
		 * @return  引数
		 */
		std::string getArgumentAsString(int index) const { return _arguments.at(index); }

		/**
		 * 指定した引数を整数として取得する。
		 *
		 * @param index 引数の序数(0-indexed)
		 * @return  引数
		 */
		int getArgumentAsInteger(int index) const;

		/**
		 * 指定した引数を倍精度浮動小数点数として取得する。
		 *
		 * @param index 引数の序数(0-indexed)
		 * @return  引数
		 */
		double getArgumentAsDouble(int index) const;
		
		/**
		 * メッセージ本体を取得する。
		 * 
		 * @return  【形式】signature(arg0,arg1,...)
		 */
		std::string getBody() const;
	private:
		void parse(std::string message);

		void parseDestinationTag(std::string::const_iterator& iter, std::string::const_iterator end);
		void parseDestinationRange(std::string::const_iterator& iter, std::string::const_iterator end);
		void parseSignature(std::string::const_iterator& iter, std::string::const_iterator end);
		void parseArguments(std::string::const_iterator& iter, std::string::const_iterator end);
		void parseArgument(std::string::const_iterator& iter, std::string::const_iterator end);
	private:
		std::string _destTag;
		int _destRange;
		std::string _signature;
		std::vector<std::string> _arguments;
	};
	using MessageParserPtr = std::shared_ptr<MessageParser>;
	using MessageParserRef = std::shared_ptr<const MessageParser>;
}
