#include "ModelResource.hpp"
#include "ModelDatabase.hpp"
#include "ModelInstance.hpp"
#include "StageModel.hpp"

namespace game {
	StageModel::StageModel(VECTOR scale, const std::string& floorFilename, const std::string& wallFilename)
		: _floor(nullptr)
		, _walls()
	{
		generate(floorFilename, wallFilename);
		init(scale);
	}

	StageModel::StageModel(ModelDatabasePtr modelDatabase, VECTOR scale, const std::string& floorFilename, const std::string& wallFilename)
		: _floor(nullptr)
		, _walls()
	{
		generate(modelDatabase, floorFilename, wallFilename);
		init(scale);
	}

	void StageModel::draw() const {
		_floor->draw();
		for (int i = 0; i < 4; ++i) {
			_walls[i]->draw();
		}
	}

	std::vector<ModelInstanceRef> StageModel::getWalls() const {
		std::vector<ModelInstanceRef> refs;
		for (auto wall : _walls) { refs.push_back(wall); }
		return refs;
	}

	std::vector<ModelInstanceRef> StageModel::getAllObjects() const {
		std::vector<ModelInstanceRef> refs;
		refs.push_back(_floor);
		for (auto wall : _walls) { refs.push_back(wall); }
		return refs;
	}

	void StageModel::generate(const std::string& floorFilename, const std::string& wallFilename) {
		// リソースの生成
		ModelResourcePtr floorResource(new ModelResource(floorFilename));
		ModelResourcePtr wallResource(new ModelResource(wallFilename));
		// インスタンスの生成
		_floor = ModelInstancePtr(new ModelInstance(floorResource));
		_walls.resize(4);
		for (int i = 0; i < 4; ++i) {
			_walls[i] = ModelInstancePtr(new ModelInstance(wallResource));
		}
	}

	void StageModel::generate(ModelDatabasePtr modelDatabase, const std::string& floorFilename, const std::string& wallFilename) {
		// リソースの生成
		auto floorResource = modelDatabase->fetch("floor", floorFilename);
		auto wallResource = modelDatabase->fetch("wall", wallFilename);
		// インスタンスの生成
		_floor = ModelInstancePtr(new ModelInstance(floorResource));
		_walls.resize(4);
		for (int i = 0; i < 4; ++i) {
			_walls[i] = ModelInstancePtr(new ModelInstance(wallResource));
		}
	}

	void StageModel::init(VECTOR scale) {
		// 床
		_floor->setScale(VGet(scale.x, 1, scale.z));
		// 壁(x軸に平行, y=0)
		_walls[0]->setScale(VGet(scale.x + 1, scale.y + 1, 1));
		_walls[0]->setAnchor(VGet(0, 0, 1));
		_walls[0]->moveTo(VGet(0, 0, 0));
		// 壁(x軸に平行, y=scale.y)
		_walls[1]->setScale(VGet(scale.x + 1, scale.y + 1, 1));
		_walls[1]->setAnchor(VGet(1, 0, 0));
		_walls[1]->moveTo(VGet(scale.x, 0, scale.z));
		// 壁(y軸に平行, x=0)
		_walls[2]->setScale(VGet(1, scale.y + 1, scale.z + 1));
		_walls[2]->setAnchor(VGet(1, 0, 1));
		_walls[2]->moveTo(VGet(0, 0, scale.z));
		// 壁(y軸に平行, x=scale.x)
		_walls[3]->setScale(VGet(1, scale.y + 1, scale.z + 1));
		_walls[3]->setAnchor(VGet(0, 0, 0));
		_walls[3]->moveTo(VGet(scale.x, 0, 0));
	}
}
