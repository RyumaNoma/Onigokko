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
		// 初期化
		void init(int playerNum);

		// プレイヤーのスケールを設定する
		void setPlayerScale(int playerId, float scale);
		// プレイヤーの位置を設定する
		void setPlayerPosition(int playerId, VECTOR position);
		// プレイヤーの基準座標を設定する
		void setPlayerAnchor(int playerId, VECTOR anchor);
		// 全てのプレイヤーのAABBを生成する
		std::vector<AABB> generateAllPlayersAABB();
		// プレイヤーの移動ベクトルを設定する
		void setPlayerMove(int playerId, VECTOR move);
		// プレイヤーの回転を計算し、設定する
		void setPlayerRotate(int playerId, VECTOR face);
		// ステージのAABBを追加する
		void addStageAABB(int minX, int minY, int minZ, int maxX, int maxY, int maxZ);
		// 衝突判定
		void check();
		// プレイヤーとステージの衝突判定
		void checkCollisionStage(const std::vector<AABB>& playerAABB);
		// プレイヤー同士の衝突判定
		void checkCollisionPlayer(const std::vector<AABB>& playerAABB);
		// 実際の動作を生成する
		std::vector<VECTOR> generateActualMove() const;
		// 実際の動作を返信する
		void responseActualMove();
		// checkCollisionに返信する
		void responseCheckCollision(int playerId1, int playerId2);
	private:
		ModelDatabasePtr _mdb;
		// 動く
		int _playerNum;
		std::vector<ModelInstancePtr> _players;
		std::vector<VECTOR> _moves;
		std::vector<float> _rotates;
		std::vector<std::vector<float>> _collisionPlayer;
		std::vector<std::pair<float, int>> _collisionStage;
		// 動かない
		std::vector<AABB> _stages;
	};
	using PhysicsPtr = std::shared_ptr<Physics>;
	using PhysicsRef = std::shared_ptr<const Physics>;
}
