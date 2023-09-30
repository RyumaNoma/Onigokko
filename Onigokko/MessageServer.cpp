#include "MessageServer.hpp"
#include "MessageParser.hpp"
#include "MessageClient.hpp"
#include <stdexcept>

namespace game {
    MessageServer::MessageServer()
    : _messages()
    , _communicators()
    {}

    int MessageServer::setCommunicator(const std::string& tag, MessageClientPtr communicator) {
        if (communicator == nullptr) {
            throw std::invalid_argument("nullptr communicator");
        }
        const int id = useNextId(tag);
        _communicators[tag][id] = communicator;

        return id;
    }

    void MessageServer::eraseCommunicator(const std::string& tag, int id) {
        auto communicator = getCommunicator(tag, id);
        if (communicator == nullptr) { return; }

        _communicators.at(tag).erase(id);
    }

    void MessageServer::receive(const std::string& message) {
        _messages.push(message);
    }

    void MessageServer::sendAll() {
        while (!isEmpty()) {
            send();
        }
    }

    void MessageServer::send() {
        if (isEmpty()) { return; }
        const auto& msg = _messages.front();
        MessageParser mp(msg);
        if (mp.isBroadcast()) {
            sendBroadcast(mp.getDestination(), mp.getBody());
        }
        else {
            auto communicator = getCommunicator(mp.getDestination(), mp.getDestinationId());
            if (communicator == nullptr) {
                _messages.pop();
                return;
            }
            communicator->receive(mp.getBody());
        }
        _messages.pop();
    }

    MessageClientPtr MessageServer::getCommunicator(const std::string& tag, int id) const {
        auto tagIter = _communicators.find(tag);
        if (tagIter == _communicators.end()) { return nullptr; }
        auto& tagCommunicators = _communicators.find(tag)->second;

        auto communicatorIter = tagCommunicators.find(id);
        if (communicatorIter == tagCommunicators.end()) { return nullptr; }
        return communicatorIter->second;
    }

    void MessageServer::sendBroadcast(const std::string& tag, const std::string& messageBody) {
        auto tagIter = _communicators.find(tag);
        if (tagIter == _communicators.end()) { return; }
        auto& tagCommunicators = _communicators.find(tag)->second;

        for (auto communicator : tagCommunicators) {
            communicator.second->receive(messageBody);
        }
    }

    int MessageServer::useNextId(const std::string& tag) {
        auto nextId = _nextIds.find(tag);
        
        if (nextId == _nextIds.end()) { // ƒ^ƒO‚ª‘¶Ý‚µ‚È‚¢ê‡
            _nextIds.emplace(tag, 1);
            return 0;
        }
        else {
            return nextId->second++;
        }
    }
}