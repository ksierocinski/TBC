#include <memory>

#include "siglot/private/callback.h"
#include "siglot/private/receivers.h"

#include "siglot/private/siglotCore.h"

namespace Siglot {

SiglotCore* SiglotCore::get() {
    static std::unique_ptr<SiglotCore> siglotCore;
    if (!siglotCore) {
        siglotCore.reset(new SiglotCore());
    }
    return siglotCore.get();
}

void SiglotCore::run()
{
    _callbackQueue.callbackLoop();
}

void SiglotCore::addCallback(std::unique_ptr<Callback> callback) {
    _callbackQueue.addCallback(std::move(callback));
}

void SiglotCore::addConnection(std::uintptr_t sender, ReceiverBase* receiver) {
    auto it = _connections.find(sender);
    if (it == _connections.end()) {
        _connections[sender] = std::unique_ptr<Receivers>{new Receivers};
    }
    _connections[sender]->addReceiver(receiver);
}

void SiglotCore::removeConnection(std::uintptr_t sender, ReceiverBase* receiver) {
    auto it = _connections.find(sender);
    if (it != _connections.end()) {
        _connections[sender]->removeReceiver(receiver);
    }
}

void SiglotCore::removeConnection(std::uintptr_t sender) {
    _connections.erase(sender);
}

void SiglotCore::removeConnection(ReceiverBase* receiver) {
    for (auto&& receivers : _connections) {
        receivers.second->removeReceiver(receiver);
    }
}

SiglotCore::~SiglotCore() = default;

} // namespace Siglot
