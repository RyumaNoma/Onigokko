#pragma once
#include "DxLib.h"
#include <string>
#include <vector>
#include <tuple>

namespace game {
class ModelParser {
public:
		/**
		 * コンストラクタ。
		 */
	ModelParser();

		/**
		 * モデル用ファイルを読み込むコンストラクタ。
		 * コンストラクタでパースも行う。
		 *
		 * @param filename モデル用ファイル
		 */
	ModelParser(const std::string& filename);

		/**
		 * 頂点バッファの参照を取得する。
		 *
		 * @return  頂点バッファの参照
		 */
	const std::vector<VERTEX3D>& getVertexBuffer() const { return _vertexBuffer; }

		/**
		 * インデックスバッファの参照を取得する。
		 *
		 * @return  インデックスバッファの参照
		 */
	const std::vector<std::vector<unsigned short>>& getIndexBuffer() const { return _indexBuffer; }
		/**
		 * 頂点数の取得。
		 * 
		 * @return  頂点数
		 */
		size_t getVertexNum() const { return _vertexBuffer.size(); }

		/**
		 * ポリゴン数の取得。
		 * 
		 * @return  ポリゴン数
		 */
		size_t getPolygonNum() const { return _indexBuffer.size(); }
private:
	void parse(const std::string& filename);
private:
	std::vector<VERTEX3D> _vertexBuffer;
	std::vector<std::vector<unsigned short>> _indexBuffer;
};
}