#include "siglot/private/callback.h"
#include "siglot/private/constRefCallback.h"
#include "siglot/private/valueCallback.h"
#include "siglot/receiver.h"

#include "siglot/private/siglotCore.h"

namespace Siglot {

namespace {
    template <class T>
    std::unique_ptr<Callback> createConstRefCallback(const T& data, Receiver<T>* receiver) {
        return new ConstRefCallback<T>{data, receiver};
    }

    template <class T>
    std::unique_ptr<Callback> createValueCallback(T&& data, Receiver<T>* receiver) {
        return new ValueCallback<T>{std::move(data), receiver};
    }
}

SiglotCore* SiglotCore::get() {
    static std::unique_ptr<SiglotCore> siglotCore;
    if (!siglotCore) {
        siglotCore.reset(new SiglotCore());
    }
    return siglotCore.get();
}

void SiglotCore::run() {
    _callbackQueue.run();
}

void SiglotCore::quitThread(std::thread::id threadId, bool force) {
    _callbackQueue.quitThread(threadId, force);
}

void SiglotCore::addConnection(std::uintptr_t sender, ReceiverBase* receiver) {
    _connections[sender].push_back(receiver);
}

void SiglotCore::removeConnection(std::uintptr_t sender, ReceiverBase* receiver) {
    _connections[sender].remove(receiver);
}

void SiglotCore::removeConnection(std::uintptr_t sender) {
    _connections.erase(sender);
}

void SiglotCore::removeConnection(ReceiverBase* receiver) {
    for (auto&& receiverList : _connections) {
        receiverList.second.remove(receiver);
    }
}

} // namespace Siglot
