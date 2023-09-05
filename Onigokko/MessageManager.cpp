#include "MessageManager.hpp"
#include "MessageParser.hpp"
#include "MessageCommunicator.hpp"
#include <stdexcept>

namespace game {
    MessageManager::MessageManager()
    : _messages()
    , _communicators()
    {}

    void MessageManager::setCommunicator(const std::string & tag, int id, MessageCommunicatorPtr communicator) {
        if (communicator == nullptr) {
            throw std::invalid_argument("nullptr communicator");
        }
        if (id < 0) {
            throw std::invalid_argument("minus id");
        }
        _communicators[tag][id] = communicator;
    }

    void MessageManager::eraseCommunicator(const std::string& tag, int id) {
        auto communicator = getCommunicator(tag, id);
        if (communicator == nullptr) { return; }

        _communicators.at(tag).erase(id);
    }

    void MessageManager::receive(const std::string& message) {
        _messages.push_back(message);
    }

    void MessageManager::sendAll() {
        for (const auto& msg : _messages) {
            MessageParser mp(msg);
            if (mp.isBroadcast()) {
                sendBroadcast(mp.getDestination(), mp.getBody());
            }
            else {
                auto communicator = getCommunicator(mp.getDestination(), mp.getDestinationId());
                if (communicator == nullptr) { continue; }
                communicator->receive(mp.getBody());
            }
        }
        _messages.clear();
    }

    MessageCommunicatorPtr MessageManager::getCommunicator(const std::string& tag, int id) const {
        auto tagIter = _communicators.find(tag);
        if (tagIter == _communicators.end()) { return nullptr; }
        auto& tagCommunicators = _communicators.find(tag)->second;

        auto communicatorIter = tagCommunicators.find(id);
        if (communicatorIter == tagCommunicators.end()) { return nullptr; }
        return communicatorIter->second;
    }

    void MessageManager::sendBroadcast(const std::string& tag, const std::string& messageBody) {
        auto tagIter = _communicators.find(tag);
        if (tagIter == _communicators.end()) { return; }
        auto& tagCommunicators = _communicators.find(tag)->second;

        for (auto communicator : tagCommunicators) {
            communicator.second->receive(messageBody);
        }
    }
}