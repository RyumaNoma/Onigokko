#include "Player.hpp"

namespace game {
	Player::Player(float oniSpeed, float personSpeed)
		: _status(STATUS::NONE)
		, _OniSpeed(oniSpeed)
		, _PersonSpeed(personSpeed)
	{}

	void Player::beOni() {
		_status = STATUS::ONI;
	}
	void Player::bePerson() {
		_status = STATUS::PERSON;
	}
	float Player::getSpeed() const {
		switch (_status)
		{
		case game::Player::STATUS::NONE:
			return 0.0f;
		case game::Player::STATUS::ONI:
			return _OniSpeed;
		case game::Player::STATUS::PERSON:
			return _PersonSpeed;
		default:
			return 0.0f;
		}
	}
}
