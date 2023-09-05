#pragma once
#include <string>
#include <vector>

namespace game {
	class MessageParser
	{
	public:
		MessageParser() = delete;
		MessageParser(const std::string& message);
	
		std::string getDestination() const { return _destTag; }
		int getDestinationId() const { return _destRange; }
		bool isBroadcast() const;
		std::string getSignature() const { return _signature; }
		std::string getArgumentAsString(int index) const { return _arguments.at(index); }
		int getArgumentAsInteger(int index) const;
		double getArgumentAsDouble(int index) const;
		std::string getBody() const;
	private:
		void parse(std::string message);

		void parseDestinationTag(std::string::const_iterator& iter);
		void parseDestinationRange(std::string::const_iterator& iter);
		void parseSignature(std::string::const_iterator& iter);
		void parseArguments(std::string::const_iterator& iter);
		void parseArgument(std::string::const_iterator& iter);
	private:
		std::string _destTag;
		int _destRange;
		std::string _signature;
		std::vector<std::string> _arguments;
	};
}
