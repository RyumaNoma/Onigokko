#pragma once
#include <memory>
#include <vector>
#include "MessageClient.hpp"

namespace game {
	class InGameInputInterface;
	using InGameInputInterfacePtr = std::shared_ptr<InGameInputInterface>;

	class InGameInput
		: public MessageClient
	{
	public:
		InGameInput(MessageServerPtr messageServer);
		virtual void receive(const std::string& message) override;

		// 入力機器のセット
		void setDevice(int playerId, InGameInputInterfacePtr device);
		InGameInputInterfacePtr getDevice(int playerId) const;
		size_t size() const { return _devices.size(); }
	private:
		void responseMove(const std::string& message);
		void responseGetItem(const std::string& message);
		void responseUseItem(const std::string& message);
	private:
		std::vector<InGameInputInterfacePtr> _devices;
	};
}
