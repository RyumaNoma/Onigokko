#pragma once
#include <vector>
#include <string>
#include <sstream>

class MessageGenerator
{
public:
	MessageGenerator();
	std::string generate() const;

	void setDestination(const std::string& destination, int id);
	void setDestinationBroadcast(const std::string& destination);
	void setSignature(const std::string& signature);
	template<class ArgType>
	void addArgument(const ArgType& argument);
	template<class ArgType>
	void updateArgument(int id, const ArgType& newArgument);

	bool isBroadcast() const;
	int getDestinationId() const { return _destRange; }
	const std::string& getSignature() const { return _signature; }
	const std::string& getArgument(int index) const { return _arguments.at(index); }
	const std::vector<std::string>& getArguments() const { return _arguments; }
private:
	std::string _destTag;
	int _destRange;
	std::string _signature;
	std::vector<std::string> _arguments;
};

template<class ArgType>
inline void MessageGenerator::addArgument(const ArgType& argument) {
	std::ostringstream oss;
	oss << argument;

	_arguments.emplace_back(oss.str());
}

template<class ArgType>
inline void MessageGenerator::updateArgument(int index, const ArgType& newArgument) {
	std::ostringstream oss;
	oss << newArgument;

	_arguments.at(index) = oss.str();
}
