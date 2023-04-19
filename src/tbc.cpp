#include "tbc/private/tbcCore.h"

#include "tbc.h"

namespace TBC {

void run() {
    TBCCore::get()->run();
}

bool processNextSignal() {
    return TBCCore::get()->processNextSignal();
}

void connect(SenderBase* sender, ReceiverBase* receiver) {
    TBCCore::get()->addConnection(reinterpret_cast<std::uintptr_t>(sender), receiver);
}

void disconnect(SenderBase* sender) {
    TBCCore::get()->removeConnection(reinterpret_cast<std::uintptr_t>(sender));
}

void disconnect(SenderBase* sender, ReceiverBase* receiver) {
    TBCCore::get()->removeConnection(reinterpret_cast<std::uintptr_t>(sender), receiver);
}

void disconnect(ReceiverBase* receiver) {
    TBCCore::get()->removeConnection(receiver);
}

} // namespace TBC
