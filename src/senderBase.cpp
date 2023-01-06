#include "siglot.h"

#include "siglot/private/senderBase.h"
#include "siglot/private/receiverBase.h"


namespace Siglot {

void SenderBase::connectTo(ReceiverBase* receiver) {
    Siglot::connect(this, receiver);
}

void SenderBase::disconnectFromAll() {
    Siglot::disconnect(this);
}

void SenderBase::disconnectFrom(ReceiverBase* receiver) {
    Siglot::disconnect(this, receiver);
}

SenderBase::~SenderBase() {
    disconnectFromAll();
}

} // namespace Siglot
