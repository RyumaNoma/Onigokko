#include "ModelResource.hpp"
#include "ModelDatabase.hpp"
#include "ModelInstance.hpp"
#include "StageModel.hpp"
#include "MessageGenerator.hpp"
#include "MessageParser.hpp"
#include "AABB.hpp"

namespace game {
	StageModel::StageModel(MessageServerPtr server, VECTOR scale, const std::string& floorFilename, const std::string& wallFilename)
		: MessageClient(server)
		, _floor(nullptr)
		, _walls()
	{
		generate(floorFilename, wallFilename);
		init(scale);
	}

	StageModel::StageModel(MessageServerPtr server, ModelDatabasePtr modelDatabase, VECTOR scale, const std::string& floorFilename, const std::string& wallFilename)
		: MessageClient(server)
		, _floor(nullptr)
		, _walls()
	{
		generate(modelDatabase, floorFilename, wallFilename);
		init(scale);
	}

	void StageModel::receive(const std::string& message) {
		MessageParser mp(message);

		if (mp.getSignature() == "getAABB") {
			responseAABB();
		}
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

	void StageModel::responseAABB() {
		AABB aabb;
		MessageGenerator mg;
		mg.setDestination("Physics", 0);
		mg.setSignature("stageAABB");

		// floor
		aabb.update(_floor);
		mg.addArgument(aabb.getMinX());
		mg.addArgument(aabb.getMinY());
		mg.addArgument(aabb.getMinZ());
		mg.addArgument(aabb.getMaxX());
		mg.addArgument(aabb.getMaxY());
		mg.addArgument(aabb.getMaxZ());
		send(mg.generate());

		// wall
		for (int i = 0; i < 4; ++i) {
			aabb.update(_walls[i]);
			mg.updateArgument(0, aabb.getMinX());
			mg.updateArgument(1, aabb.getMinY());
			mg.updateArgument(2, aabb.getMinZ());
			mg.updateArgument(3, aabb.getMaxX());
			mg.updateArgument(4, aabb.getMaxY());
			mg.updateArgument(5, aabb.getMaxZ());
			send(mg.generate());
		}
	}
}
