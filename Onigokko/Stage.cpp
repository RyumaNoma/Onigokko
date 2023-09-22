#include "Stage.hpp"
#include "ModelResource.hpp"
#include "ModelDatabase.hpp"
#include "ModelInstance.hpp"

namespace {
	const char* FLOOR_FILEPATH = "ground.txt";
	const char* WALL_FILEPATH = "wall.txt";
}

namespace game {
	Stage::Stage(DxLib::VECTOR scale)
		: _floor(nullptr)
		, _walls()
	{
		generate();
		init(scale);
	}

	Stage::Stage(ModelDatabasePtr modelDatabase, DxLib::VECTOR scale)
		: _floor(nullptr)
		, _walls()
	{
		generate(modelDatabase);
		init(scale);
	}

	void Stage::draw() const {
		_floor->draw();
		for (int i = 0; i < 4; ++i) {
			_walls[i]->draw();
		}
	}

	std::vector<ModelInstanceRef> Stage::getWalls() const {
		std::vector<ModelInstanceRef> refs;
		for (auto wall : _walls) { refs.push_back(wall); }
		return refs;
	}

	std::vector<ModelInstanceRef> Stage::getAllObjects() const {
		std::vector<ModelInstanceRef> refs;
		refs.push_back(_floor);
		for (auto wall : _walls) { refs.push_back(wall); }
		return refs;
	}

	void Stage::generate() {
		// リソースの生成
		ModelResourcePtr floorResource(new ModelResource(FLOOR_FILEPATH));
		ModelResourcePtr wallResource(new ModelResource(WALL_FILEPATH));
		// インスタンスの生成
		_floor = ModelInstancePtr(new ModelInstance(floorResource));
		_walls.resize(4);
		for (int i = 0; i < 4; ++i) {
			_walls[i] = ModelInstancePtr(new ModelInstance(wallResource));
		}
	}

	void Stage::generate(ModelDatabasePtr modelDatabase) {
		auto floorResource = modelDatabase->fetch("floor", FLOOR_FILEPATH);
		auto wallResource = modelDatabase->fetch("wall", WALL_FILEPATH);
		// インスタンスの生成
		_floor = ModelInstancePtr(new ModelInstance(floorResource));
		_walls.resize(4);
		for (int i = 0; i < 4; ++i) {
			_walls[i] = ModelInstancePtr(new ModelInstance(wallResource));
		}
	}

	void Stage::init(DxLib::VECTOR scale) {
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
