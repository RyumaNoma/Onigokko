#include "MessageGenerator.hpp"
#include <sstream>
#include <cctype>
#define DESTINATION_BROADCAST (-1)

MessageGenerator::MessageGenerator()
: _destTag("")
, _destRange(0)
, _signature("")
, _arguments()
{}

std::string MessageGenerator::generate() const {
	std::ostringstream oss;
	// 宛先タグ1
	if (_destTag.empty()) { throw std::runtime_error("empty destination tag"); }
	oss << '[' << _destTag << ']';
	// 宛先タグ2
	if (_destRange == -1) {
		oss << "[Broadcast]";
	}
	else {
		oss << '[' << _destRange << ']';
	}
	// シグネチャ
	if (_signature.empty()) { throw std::runtime_error("empty signature"); }
	oss << _signature;
	// 引数
	oss << '(';
	if (!_arguments.empty()) {
		for (int i = 0; i < _arguments.size() - 1; ++i) {
			oss << _arguments[i] << ',';
		}
		oss << _arguments.back();
	}
	oss << ')';

	return oss.str();
}

void MessageGenerator::setDestination(const std::string& destination, int id) {
	if (destination.empty()) { throw std::invalid_argument("empty destination tag"); }
	if (id < 0) { throw std::invalid_argument("minus destination id"); }

	_destTag = destination;
	_destRange = id;
}

void MessageGenerator::setDestinationBroadcast(const std::string& destination) {
	if (destination.empty()) { throw std::invalid_argument("empty destination tag"); }

	_destTag = destination;
	_destRange = -1;
}

void MessageGenerator::setSignature(const std::string& signature) {
	if (signature.empty()) { throw std::invalid_argument("empty signature"); }
	for (char c : signature) {
		if (!isValidSignatureCharacter(c)) {
			throw std::invalid_argument("signature include bad character");
		}
	}

	_signature = signature;
}

bool MessageGenerator::isBroadcast() const {
	return (_destRange == DESTINATION_BROADCAST);
}

bool MessageGenerator::isValidSignatureCharacter(char c) const
{
	return (std::isdigit(c) || std::isalpha(c) || c == '.' || c == '_' || c == '-');
}

