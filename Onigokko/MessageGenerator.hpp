#pragma once
#include <vector>
#include <string>
#include <sstream>

class MessageGenerator
{
public:
	MessageGenerator();
	std::string generate() const;

	void setDestination(std::string destination, int id);
	void setDestinationBroadCast(std::string destination);

	bool isBroadCast() const;
	int getDestinationId() const { return _destRange; }
	const std::string& getSignature() const { return _signature; }
	const std::vector<std::string>& getArguments() const { return _arguments; }
private:
	std::string _destTag;
	int _destRange;
	std::string _signature;
	std::vector<std::string> _arguments;
};

