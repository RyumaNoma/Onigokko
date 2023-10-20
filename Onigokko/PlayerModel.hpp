#pragma once

namespace game {
	class ModelDatabase;
	using ModelDatabasePtr = std::shared_ptr<ModelDatabase>;

	class ModelInstance;
	using ModelInstancePtr = std::shared_ptr<ModelInstance>;
	using ModelInstanceRef = std::shared_ptr<const ModelInstance>;

	class PlayerModel
		: public MessageClient
	{
	public:
		PlayerModel(MessageServerPtr server, ModelDatabasePtr modelDatabase, float scale, const std::string& modelFilename);

		void receive(const std::string& message) override;

		void draw() const;

		float getSpeed() const { return _speed; }

		ModelInstanceRef getModelInstance() const { return _model; }
	private:
		ModelInstancePtr _model;
		float _speed;
	};
	using PlayerModelPtr = std::shared_ptr<PlayerModel>;
	using PlayerModelRef = std::shared_ptr<const PlayerModel>;
}
