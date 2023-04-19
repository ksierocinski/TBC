#include "tbc.h"

#include "tbc/private/senderBase.h"
#include "tbc/private/receiverBase.h"


namespace TBC {

void SenderBase::connectTo(ReceiverBase* receiver) {
    TBC::connect(this, receiver);
}

void SenderBase::disconnectFromAll() {
    TBC::disconnect(this);
}

void SenderBase::disconnectFrom(ReceiverBase* receiver) {
    TBC::disconnect(this, receiver);
}

SenderBase::~SenderBase() {
    disconnectFromAll();
}

} // namespace TBC
