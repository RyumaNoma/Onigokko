#pragma once
#include "MessageClient.hpp"

namespace game {
	class Physics
		: public MessageClient
	{
	public:
		void receive(const std::string& message) override;
	};
}
