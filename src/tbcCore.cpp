#include "tbc/private/callback.h"
#include "tbc/private/constRefCallback.h"
#include "tbc/private/valueCallback.h"
#include "tbc/receiver.h"

#include "tbc/private/tbcCore.h"

namespace TBC {

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

TBCCore* TBCCore::get() {
    static std::unique_ptr<TBCCore> tbcCore;
    if (!tbcCore) {
        tbcCore.reset(new TBCCore());
    }
    return tbcCore.get();
}

void TBCCore::run() {
    _callbackQueue.run();
}

bool TBCCore::processNextSignal() {
    return _callbackQueue.processNextCallback();
}

void TBCCore::quitThread(std::thread::id threadId, bool force) {
    _callbackQueue.quitThread(threadId, force);
}

void TBCCore::addConnection(std::uintptr_t sender, ReceiverBase* receiver) {
    _connections[sender].push_back(receiver);
}

void TBCCore::removeConnection(std::uintptr_t sender, ReceiverBase* receiver) {
    _connections[sender].remove(receiver);
}

void TBCCore::removeConnection(std::uintptr_t sender) {
    _connections.erase(sender);
}

void TBCCore::removeConnection(ReceiverBase* receiver) {
    for (auto&& receiverList : _connections) {
        receiverList.second.remove(receiver);
    }
}

} // namespace TBC
