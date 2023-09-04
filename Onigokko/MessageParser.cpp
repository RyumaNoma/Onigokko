#include "MessageParser.hpp"
#include <stdexcept>

namespace {
	constexpr int BROADCAST_RANGE = -1;

	enum class PARSE_STATE {
		DESTINATION_TAG,
		DESTINATION_RANGE,
		SIGNATURE,
		ARGUMENTS,
		END
	};
}

namespace game {
	MessageParser::MessageParser(const std::string& message)
		: _destTag()
		, _destRange(0)
		, _signature()
		, _arguments()
	{
		parse(message);
	}

	bool MessageParser::isBroadcast() const {
		return (_destRange == BROADCAST_RANGE);
	}
	
	int MessageParser::getArgumentAsInteger(int index) const {
		return std::stoi(_arguments.at(index));
	}

	double MessageParser::getArgumentAsDouble(int index) const {
		return std::stod(_arguments.at(index));
	}

	void MessageParser::parse(std::string message) {
		std::string::const_iterator iter = message.begin();
		PARSE_STATE state = PARSE_STATE::DESTINATION_TAG;

		while (iter != message.end()) {
			switch (state)
			{
			case PARSE_STATE::DESTINATION_TAG:
				parseDestinationTag(iter);
				state = PARSE_STATE::DESTINATION_RANGE;
				break;
			case PARSE_STATE::DESTINATION_RANGE:
				parseDestinationRange(iter);
				state = PARSE_STATE::SIGNATURE;
				break;
			case PARSE_STATE::SIGNATURE:
				parseSignature(iter);
				state = PARSE_STATE::ARGUMENTS;
				break;
			case PARSE_STATE::ARGUMENTS:
				parseArguments(iter);
				state = PARSE_STATE::END;
				break;
			default:
				throw std::runtime_error("uncatched parse state");
			}
		}
	}

	void MessageParser::parseDestinationTag(std::string::const_iterator& iter) {
		if (*iter == '[') {
			++iter;
		}
		else {
			throw std::runtime_error("destination tag must start with [");
		}

		while (*iter != ']') {
			_destTag.push_back(*iter);
			++iter;
		}
		++iter;
	}

	void MessageParser::parseDestinationRange(std::string::const_iterator& iter) {
		if (*iter == '[') {
			++iter;
		}
		else {
			throw std::runtime_error("destination range must start with [");
		}

		std::string destRange;
		while (*iter != ']') {
			destRange.push_back(*iter);
			++iter;
		}
		if (destRange == "Broadcast") {
			_destRange = -1;
		}
		else {
			_destRange = std::stoi(destRange);
		}
		++iter;
	}

	void MessageParser::parseSignature(std::string::const_iterator& iter) {
		while (*iter != '(') {
			_signature.push_back(*iter);
			++iter;
		}
	}
	void MessageParser::parseArguments(std::string::const_iterator& iter) {
		if (*iter == '(') {
			++iter;
		}
		else {
			throw std::runtime_error("arguments must start with (");
		}

		while (*iter != ')') {
			if (*iter == ',') {
				++iter;
			}
			else {
				parseArgument(iter);
			}
		}
		++iter;
	}
	void MessageParser::parseArgument(std::string::const_iterator& iter) {
		_arguments.push_back("");
		while (*iter != ',' && *iter != ')') {
			_arguments.back().push_back(*iter);
			++iter;
		}
	}
}