#include "pch.h"
#include "Player.hpp"

namespace game {
	TEST_CLASS(PlayerTest)
	{
	public:
		TEST_METHOD(DefaultConstructor) {
			Player player(2.0, 1.0);

			Assert::AreEqual(Player::STATUS::NONE, player.getStatus());
			Assert::AreEqual(0.0f, player.getSpeed());
		}
		TEST_METHOD(NONEToOni) {
			Player player(2.0, 1.0);

			player.beOni();

			Assert::AreEqual(Player::STATUS::ONI, player.getStatus());
			Assert::AreEqual(2.0f, player.getSpeed());
		}
		TEST_METHOD(NONOETOPerson) {
			Player player(2.0, 1.0);

			player.bePerson();

			Assert::AreEqual(Player::STATUS::PERSON, player.getStatus());
			Assert::AreEqual(1.0f, player.getSpeed());
		}
		TEST_METHOD(OniToOni) {
			Player player(2.0, 1.0);

			player.beOni();
			player.beOni();

			Assert::AreEqual(Player::STATUS::ONI, player.getStatus());
			Assert::AreEqual(2.0f, player.getSpeed());
		}
		TEST_METHOD(OniToPerson) {
			Player player(2.0, 1.0);

			player.beOni();
			player.bePerson();

			Assert::AreEqual(Player::STATUS::PERSON, player.getStatus());
			Assert::AreEqual(1.0f, player.getSpeed());
		}
		TEST_METHOD(PersonToOni) {
			Player player(2.0, 1.0);

			player.bePerson();
			player.beOni();

			Assert::AreEqual(Player::STATUS::ONI, player.getStatus());
			Assert::AreEqual(2.0f, player.getSpeed());
		}
		TEST_METHOD(PersonToPerson) {
			Player player(2.0, 1.0);

			player.bePerson();
			player.bePerson();

			Assert::AreEqual(Player::STATUS::PERSON, player.getStatus());
			Assert::AreEqual(1.0f, player.getSpeed());
		}
	};
}
