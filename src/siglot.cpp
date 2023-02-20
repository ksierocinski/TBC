#include "siglot/private/siglotCore.h"

#include "siglot.h"

namespace Siglot {

void run() {
    SiglotCore::get()->run();
}

bool processNextSignal() {
    return SiglotCore::get()->processNextSignal();
}

void connect(SenderBase* sender, ReceiverBase* receiver) {
    SiglotCore::get()->addConnection(reinterpret_cast<std::uintptr_t>(sender), receiver);
}

void disconnect(SenderBase* sender) {
    SiglotCore::get()->removeConnection(reinterpret_cast<std::uintptr_t>(sender));
}

void disconnect(SenderBase* sender, ReceiverBase* receiver) {
    SiglotCore::get()->removeConnection(reinterpret_cast<std::uintptr_t>(sender), receiver);
}

void disconnect(ReceiverBase* receiver) {
    SiglotCore::get()->removeConnection(receiver);
}

} // namespace Siglot
