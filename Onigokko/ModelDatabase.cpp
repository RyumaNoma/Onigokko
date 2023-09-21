#include "ModelDatabase.hpp"
#include "ModelResource.hpp"

namespace game {
	ModelDatabase::ModelDatabase()
		: _resources()
	{}
	
	void ModelDatabase::load(const std::string & filename) {
		ModelResourcePtr model(new ModelResource(filename));
		_resources.emplace(filename, model);
	}
	
	ModelResourcePtr ModelDatabase::fetch(const std::string& filename) {
		if (_resources.find(filename) == _resources.end()) {
			load(filename);
		}
		return _resources.at(filename);
	}
}
