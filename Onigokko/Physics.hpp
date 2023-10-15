#pragma once
#include "MessageClient.hpp"
#include "DxLib.h"
#include <vector>

namespace game {
	class ModelInstance;
	class AABB;

	class Physics
		: public MessageClient
	{
	public:
		void receive(const std::string& message) override;
	private:
		// 動く
		std::vector<ModelInstance> _models;
		std::vector<AABB> _dynamicObjects;
		std::vector<VECTOR> _moves;
		std::vector<float> _rotates;
		// 動かない
		std::vector<AABB> _staticObjects;
	};
}
