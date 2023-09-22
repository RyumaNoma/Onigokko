#include "ModelDatabase.hpp"
#include "ModelResource.hpp"

namespace game {
	ModelDatabase::ModelDatabase()
		: _resources()
	{}
	
	void ModelDatabase::load(const std::string& key, const std::string & filename) {
		ModelResourcePtr model(new ModelResource(filename));
		_resources.emplace(key, model);
	}
	
	ModelResourcePtr ModelDatabase::fetch(const std::string& key, const std::string& filename) {
		if (_resources.find(key) == _resources.end()) {
			load(key, filename);
		}
		return _resources.at(key);
	}
}
