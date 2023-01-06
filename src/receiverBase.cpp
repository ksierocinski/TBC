#include "siglot.h"

#include "siglot/private/receiverBase.h"

namespace Siglot {

void ReceiverBase::connectTo(SenderBase* sender)
{
    Siglot::connect(sender, this);
}
    
void ReceiverBase::disconnectFromAll() {
    Siglot::disconnect(this);
}

void ReceiverBase::disconnectFrom(SenderBase* sender)
{
    Siglot::disconnect(sender, this);
}

ReceiverBase::~ReceiverBase() {
    disconnectFromAll();
}

} // namespace Siglot
