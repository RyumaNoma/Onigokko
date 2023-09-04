#pragma once
#include <string>
#include <vector>

class MessageParser
{
public:
	MessageParser() = delete;
	MessageParser(const std::string& message);
	
	std::string getDestination() const;
	int getDestinationId() const;
	bool isBroadcast() const;
	std::string getSignature() const;
	std::string getArgumentAsString(int index) const;
	int getArgumentAsInteger(int index) const;
	double getArgumentAsDouble(int index) const;
private:
	void parse(const std::string& message);
private:
	std::string _destTag;
	int _destRange;
	std::string _signature;
	std::vector<std::string> _arguments;
};

