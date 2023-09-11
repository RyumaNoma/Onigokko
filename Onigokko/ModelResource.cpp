#include "ModelResource.hpp"
#include "ModelParser.hpp"

#define SAFE_DELETE(ptr); delete[] ptr; ptr = nullptr;

namespace game {
	ModelResource::ModelResource()
		: _filepath()
		, _vertexBuffer(nullptr)
		, _vertexNum(0)
		, _indexBuffer(nullptr)
		, _polygonNum(0)
	{}

	ModelResource::ModelResource(std::string filepath) {
		setFilepath(filepath);
		load();
	}

	ModelResource::ModelResource(const ModelResource& mr)
		: _filepath(mr._filepath)
		, _vertexBuffer(new VERTEX3D[mr._vertexNum])
		, _vertexNum(mr._vertexNum)
		, _indexBuffer(new unsigned short[mr._polygonNum * 3])
		, _polygonNum(mr._polygonNum)
	{
		for (int i = 0; i < _vertexNum; ++i) {
			_vertexBuffer[i] = mr._vertexBuffer[i];
		}
		for (int i = 0; i < _polygonNum * 3; ++i) {
			_indexBuffer[i] = mr._indexBuffer[i];
		}
	}

	ModelResource& ModelResource::operator=(const ModelResource& mr) {
		destroy();
		_filepath = mr._filepath;
		_vertexNum = mr._vertexNum;
		_polygonNum = mr._polygonNum;
		_vertexBuffer = new VERTEX3D[_vertexNum];
		_indexBuffer = new unsigned short[_polygonNum * 3];
		for (int i = 0; i < _vertexNum; ++i) {
			_vertexBuffer[i] = mr._vertexBuffer[i];
		}
		for (int i = 0; i < _polygonNum * 3; ++i) {
			_indexBuffer[i] = mr._indexBuffer[i];
		}
		return *this;
	}

	ModelResource::~ModelResource() {
		destroy();
	}

	void ModelResource::reload() {
		destroy();
		load();
	}

	void ModelResource::setFilepath(const std::string& filepath) {
		_filepath = filepath;
	}

	void ModelResource::destroy() {
		SAFE_DELETE(_vertexBuffer);
		SAFE_DELETE(_indexBuffer);
		_vertexNum = 0;
		_polygonNum = 0;
	}

	void ModelResource::load() {
		ModelParser mp(_filepath);

		_vertexNum = mp.getVertexNum();
		_polygonNum = mp.getPolygonNum();

		const auto& vb = mp.getVertexBuffer();
		const auto& ib = mp.getIndexBuffer();

		_vertexBuffer = new VERTEX3D[_vertexNum];
		for (int i = 0; i < _vertexNum; ++i) {
			_vertexBuffer[i] = vb[i];
		}

		_indexBuffer = new unsigned short[_polygonNum * 3];
		for (int poly = 0; poly < _polygonNum; ++poly) {
			for (int i = 0; i < 3; ++i) {
				int index = poly * 3 + i;
				_indexBuffer[index] = ib[poly][i];
			}
		}
	}
}
#undef SAFE_DELETE