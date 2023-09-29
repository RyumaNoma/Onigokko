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

	std::string MessageParser::getBody() const {
		std::string body = _signature;
		body.push_back('(');
		if (!_arguments.empty()) {
			for (int i = 0; i < _arguments.size() - 1; ++i) {
				body += _arguments[i] + ',';
			}
			body += _arguments.back();
		}
		body.push_back(')');
		return body;
	}

	void MessageParser::parse(std::string message) {
		std::string::const_iterator iter = message.begin();
		PARSE_STATE state = PARSE_STATE::DESTINATION_TAG;
		if (*iter != '[') {
			state = PARSE_STATE::SIGNATURE;
		}

		while (iter != message.end()) {
			switch (state)
			{
			case PARSE_STATE::DESTINATION_TAG:
				parseDestinationTag(iter, message.end());
				state = PARSE_STATE::DESTINATION_RANGE;
				break;
			case PARSE_STATE::DESTINATION_RANGE:
				parseDestinationRange(iter, message.end());
				state = PARSE_STATE::SIGNATURE;
				break;
			case PARSE_STATE::SIGNATURE:
				parseSignature(iter, message.end());
				state = PARSE_STATE::ARGUMENTS;
				break;
			case PARSE_STATE::ARGUMENTS:
				parseArguments(iter, message.end());
				state = PARSE_STATE::END;
				break;
			default:
				throw std::runtime_error("uncatched parse state");
			}
		}
	}

	void MessageParser::parseDestinationTag(std::string::const_iterator& iter, std::string::const_iterator end) {
		if (iter == end) { throw std::runtime_error("not exist destination tag"); }
		if (*iter == '[') {
			++iter;
		}
		else {
			throw std::runtime_error("destination tag must start with [");
		}
		if (iter == end) { throw std::runtime_error("destination tag end with ["); }

		while (*iter != ']') {
			_destTag.push_back(*iter);
			++iter;
			if (iter == end) { throw std::runtime_error("not close destination tag"); }
		}
		++iter;
	}

	void MessageParser::parseDestinationRange(std::string::const_iterator& iter, std::string::const_iterator end) {
		if (iter == end) { throw std::runtime_error("not exist destination range"); }
		if (*iter == '[') {
			++iter;
		}
		else {
			throw std::runtime_error("destination range must start with [");
		}
		if (iter == end) { throw std::runtime_error("destination range end with ["); }

		std::string destRange;
		while (*iter != ']') {
			destRange.push_back(*iter);
			++iter;
			if (iter == end) { throw std::runtime_error("not close destination range"); }
		}
		if (destRange == "Broadcast") {
			_destRange = BROADCAST_RANGE;
		}
		else {
			_destRange = std::stoi(destRange);
		}
		++iter;
	}

	void MessageParser::parseSignature(std::string::const_iterator& iter, std::string::const_iterator end) {
		if (iter == end) { throw std::runtime_error("not exist signature"); }
		while (*iter != '(') {
			_signature.push_back(*iter);
			++iter;
			if (iter == end) { throw std::runtime_error("not close signature"); }
		}
	}
	void MessageParser::parseArguments(std::string::const_iterator& iter, std::string::const_iterator end) {
		if (iter == end) { throw std::runtime_error("not exist arguments"); }
		if (*iter == '(') {
			++iter;
			if (iter == end) { throw std::runtime_error("arguments end with ("); }
		}
		else {
			throw std::runtime_error("arguments must start with (");
		}
		while (*iter != ')') {
			if (*iter == ',') {
				++iter;
			}
			else {
				parseArgument(iter, end);
			}
			if (iter == end) { throw std::runtime_error("not close arguments"); }
		}
		++iter;
	}
	void MessageParser::parseArgument(std::string::const_iterator& iter, std::string::const_iterator end) {
		if (iter == end) { throw std::runtime_error("not exist argument"); }
		_arguments.push_back("");
		while (*iter != ',' && *iter != ')') {
			_arguments.back().push_back(*iter);
			++iter;
			if (iter == end) { throw std::runtime_error("not close argument"); }
		}
	}
}