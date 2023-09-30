#include "InGameInput.hpp"
#include "MessageParser.hpp"
#include "InGameInputInterface.hpp"
#include "MessageGenerator.hpp"
#include "MessageServer.hpp"

namespace game {
	InGameInput::InGameInput(MessageServerPtr messageServer)
		: MessageClient(messageServer)
		, _devices()
	{}

	void InGameInput::receive(const std::string& message) {
		MessageParser mp(message);
		const auto signature = mp.getSignature();

		if (signature == "checkMoveInput") {
			responseMove(message);
		}
		else if (signature == "checkGetItemInput") {
			responseGetItem(message);
		}
		else if (signature == "checkUseItemInput") {
			responseUseItem(message);
		}
	}

	void InGameInput::setDevice(int playerId, InGameInputInterfacePtr device) {
		_devices.resize(playerId + 1, nullptr);
		_devices[playerId] = device;
	}

	InGameInputInterfacePtr InGameInput::getDevice(int playerId) const {
		if (playerId < _devices.size()) {
			return _devices[playerId];
		}
		return nullptr;
	}

	void InGameInput::responseMove(const std::string& message) {
		MessageParser mp(message);
		const int id = mp.getArgumentAsInteger(0);
		// �f�o�C�X�̎擾
		auto device = getDevice(id);
		if (device == nullptr) { return; }
		// �ړ����͂̎擾
		const auto move = device->move();
		if (move == InGameInputInterface::MOVE_DIRECTION::NONE) { return; }
		// ���X�|���X�̍쐬�E���M
		MessageGenerator mg;
		mg.setDestination("Game", 0);
		mg.setSignature("move");
		mg.addArgument(id);
		mg.addArgument(move);
		MessageClient::send(mg.generate());
	}

	void InGameInput::responseGetItem(const std::string& message) {
		MessageParser mp(message);
		const int id = mp.getArgumentAsInteger(0);
		// �f�o�C�X�̎擾
		auto device = getDevice(id);
		if (device == nullptr) { return; }
		// �A�C�e���擾�̎擾
		const auto getItem = device->getSkillItem();
		if (!getItem) { return; }
		// ���X�|���X�̍쐬�E���M
		MessageGenerator mg;
		mg.setDestination("Game", 0);
		mg.setSignature("getItem");
		mg.addArgument(id);
		MessageClient::send(mg.generate());
	}

	void InGameInput::responseUseItem(const std::string& message) {
		MessageParser mp(message);
		const int id = mp.getArgumentAsInteger(0);
		// �f�o�C�X�̎擾
		auto device = getDevice(id);
		if (device == nullptr) { return; }
		// �A�C�e���g�p�̎擾
		const auto useItem = device->getSkillItem();
		if (!useItem) { return; }
		// ���X�|���X�̍쐬�E���M
		MessageGenerator mg;
		mg.setDestination("Game", 0);
		mg.setSignature("useItem");
		mg.addArgument(id);
		MessageClient::send(mg.generate());
	}
}
