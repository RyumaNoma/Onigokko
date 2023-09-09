#pragma once
#include "DxLib.h"
#include <string>
#include <vector>
#include <tuple>

class ModelParser {
public:
	ModelParser();
	ModelParser(const std::string& filename);

	const std::vector<VERTEX3D>& getVertexBuffer() const { return _vertexBuffer; }
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
