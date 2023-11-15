#pragma once
#include "MessageClient.hpp"
#include "DxLib.h"
#include <vector>

namespace game {
	class ModelInstance;
	using ModelInstancePtr = std::shared_ptr<ModelInstance>;
	class AABB;
	class ModelDatabase;
	using ModelDatabasePtr = std::shared_ptr<ModelDatabase>;

	class Physics
		: public MessageClient
	{
	public:
		Physics(MessageServerPtr server, ModelDatabasePtr modelDatabase);
		void receive(const std::string& message) override;

		/**
		 * @brief プレイヤー同士が衝突した時刻。
		 * @brief check()ののちに呼び出す必要あり
		 * 
		 * @param playerId1 プレイヤー1
		 * @param playerId2 プレイヤー2
		 * @return  0.0~1.0の間の時刻（衝突していないなら2.0）
		 */
		float collidedTime(int playerId1, int playerId2) const { return _collisionPlayer.at(playerId1).at(playerId2); }
		
		/**
		 * @brief プレイヤー同士の衝突判定。
		 * @brief check()ののちに呼び出す必要あり
		 * 
		 * @param playerId1 プレイヤー1
		 * @param playerId2 プレイヤー2
		 * @return  衝突したらtrue
		 */
		bool isCollided(int playerId1, int playerId2) const { return _collisionPlayer.at(playerId1).at(playerId2) <= 1.0f; }
		
		/**
		 * @brief プレイヤーがステージに衝突したかの判定。
		 * 
		 * @param playerId プレイヤー
		 * @return 衝突したらtrue
		 */
		bool isCollidedStage(int playerId) const { return _collisionStage.at(playerId).first <= 1.0f; }
	private:
		// 動く
		std::vector<ModelInstance> _models;
		std::vector<AABB> _dynamicObjects;
		std::vector<VECTOR> _moves;
		std::vector<float> _rotates;
		// 動かない
		std::vector<AABB> _staticObjects;
	};
	using PhysicsPtr = std::shared_ptr<Physics>;
	using PhysicsRef = std::shared_ptr<const Physics>;
}
