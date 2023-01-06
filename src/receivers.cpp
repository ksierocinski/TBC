#include "siglot/private/receivers.h"

namespace Siglot {

void Receivers::addReceiver(ReceiverBase* receiver) {
    _receivers.push_back(receiver);
}

void Receivers::removeReceiver(ReceiverBase* receiver) {
    _receivers.remove(receiver);
}

} // namespace Siglot
