#include "ModelParser.hpp"
#include <fstream>
#include <cctype>
#include <set>
#include <stdexcept>

namespace {
	enum class TOKEN {
		NONE,
		VERTEX_START,
		VERTEX_END,
		INDEX_START,
		INDEX_END,
		LEFT_PAR,
		RIGHT_PAR,
		KEY_POS,
		KEY_NORM,
		KEY_DIF,
		KEY_SPC,
		KEY_U,
		KEY_V,
		KEY_SU,
		KEY_SV,
		EQ,
		MINUS,
		COMMA,
		PERIOD,
		DIGIT,
		END
	};
}

namespace game {
	ModelParser::ModelParser()
		: _vertexBuffer()
		, _indexBuffer()
	{}

	ModelParser::ModelParser(const std::string & filename)
		: _vertexBuffer()
		, _indexBuffer()
	{
		parse(filename);
	}

	void ModelParser::parse(const std::string& filename) {
		std::ifstream in(filename);
		if (!in.is_open()) { throw std::invalid_argument("could not open " + filename); }

		// モデルファイルをひとつの文字列につなげる(改行無し)
		std::string model;
		std::string line;
		while (std::getline(in, line)) {
			model += line;
		}
		in.close();

		// 空白の削除
		eraseSpace(model);

		// パース
		int pos = 0;
		while (pos + 1 < model.size()) {
			if (model[pos + 1] == 'v') {
				parseVertex(pos, model);
			}
			else if (model[pos + 1] == 'i') {
				parseIndex(pos, model);
			}
			else {
				break;
			}
		}
	}
	
	void ModelParser::eraseSpace(std::string& model) {
		std::string::const_iterator read = model.begin();
		std::string::iterator push = model.begin();

		while (read != model.end()) {
			if (std::isspace(*read)) {
				++read;
			}
			else {
				*push = *read;
				++push;
				++read;
			}
		}
		model.resize(push - model.begin());
		model.shrink_to_fit();
	}

	void ModelParser::parseVertex(int& pos, const std::string& model) {
		if (pos >= model.size()) { throw std::runtime_error("not exist vertex"); }

		// 開始タグ
		auto startTag = model.substr(pos, 3);
		if (startTag != "<v>") { throw std::runtime_error("it is not vertex start tag"); }
		pos += 3;
		_vertexBuffer.push_back(VERTEX3D());
		// 属性
		while (pos < model.size() && model[pos] != '<') {
			parseVertexAttribute(pos, model);
			if (model[pos] == ',') {
				++pos;
			}
		}
		// 終了タグ
		auto endTag = model.substr(pos, 4);
		if (endTag != "</v>") { throw std::runtime_error("it is not vertex end tag"); }
		pos += 4;
	}

	void ModelParser::parseVertexAttribute(int& pos, const std::string& model) {
		std::string key, value;
		
		// key
		while (pos < model.size() && model[pos] != '=') {
			key.push_back(model[pos]);
			++pos;
		}
		// equal
		if (pos < model.size() && model[pos] == '=') {
			++pos;
		}

		// value
		if (key == "pos") {
			VECTOR value = parseVector(pos, model);
			_vertexBuffer.back().pos = value;
		}
		else if (key == "norm") {
			VECTOR value = parseVector(pos, model);
			_vertexBuffer.back().norm = value;
		}
		else if (key == "dif") {
			COLOR_U8 value = parseColor(pos, model);
			_vertexBuffer.back().dif = value;
		}
		else if (key == "spc") {
			COLOR_U8 value = parseColor(pos, model);
			_vertexBuffer.back().spc = value;
		}
		else if (key == "u") {
			float value = parseFloat(pos, model);
			_vertexBuffer.back().u = value;
		}
		else if (key == "v") {
			float value = parseFloat(pos, model);
			_vertexBuffer.back().v = value;
		}
		else if (key == "su") {
			float value = parseFloat(pos, model);
			_vertexBuffer.back().su = value;
		}
		else if (key == "sv") {
			float value = parseFloat(pos, model);
			_vertexBuffer.back().sv = value;
		}
	}
	void ModelParser::parseIndex(int& pos, const std::string& model) {
		// 開始タグ
		auto startTag = model.substr(pos, 3);
		if (startTag != "<i>") { throw std::runtime_error("it is not index start tag"); }
		pos += 3;
		// インデックス
		_indexBuffer.push_back(std::vector<unsigned short>(3));
		for (int i = 0; i < 3; ++i) {
			_indexBuffer.back()[i] = static_cast<unsigned short>(parseInteger(pos, model));
			if (pos < model.size() && model[pos] == ',') { ++pos; }
		}
		// )
		if (pos < model.size() && model[pos] == ')') { ++pos; }
		// 終了タグ
		auto endTag = model.substr(pos, 4);
		if (endTag != "</i>") { throw std::runtime_error("it is not index end tag"); }
		pos += 4;
	}
	
	int ModelParser::parseInteger(int& pos, const std::string& model) {
		std::string numStr;
		while (pos < model.size() && std::isdigit(model[pos])) {
			numStr.push_back(model[pos]);
			++pos;
		}
		return std::stoi(numStr);
	}

	float ModelParser::parseFloat(int& pos, const std::string& model) {
		std::string numStr;
		while (pos < model.size() &&
			(model[pos] == '.' || std::isdigit(model[pos]) || model[pos] == '-')) {
			numStr.push_back(model[pos]);
			++pos;
		}
		return std::stof(numStr);
	}

	VECTOR ModelParser::parseVector(int& pos, const std::string& model) {
		VECTOR vec;
		// (
		if (pos < model.size() && model[pos] == '(') { ++pos; }
		// x
		vec.x = parseFloat(pos, model);
		if (pos < model.size() && model[pos] == ',') { ++pos; }
		// y
		vec.y = parseFloat(pos, model);
		if (pos < model.size() && model[pos] == ',') { ++pos; }
		// z
		vec.z = parseFloat(pos, model);
		// )
		if (pos < model.size() && model[pos] == ')') { ++pos; }
		return vec;
	}

	COLOR_U8 ModelParser::parseColor(int& pos, const std::string& model) {
		COLOR_U8 color;
		// (
		if (pos < model.size() && model[pos] == '(') { ++pos; }
		// r
		color.r = parseInteger(pos, model);
		if (pos < model.size() && model[pos] == ',') { ++pos; }
		// g
		color.g = parseInteger(pos, model);
		if (pos < model.size() && model[pos] == ',') { ++pos; }
		// b
		color.b = parseInteger(pos, model);
		if (pos < model.size() && model[pos] == ',') { ++pos; }
		// a
		color.a = parseInteger(pos, model);
		// )
		if (pos < model.size() && model[pos] == ')') { ++pos; }
		return color;
	}

}
