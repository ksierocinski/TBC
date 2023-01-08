#include <iostream>

#include "siglot.h"

#include "siglot/private/receiverBase.h"
#include "siglot/private/siglotCore.h"

namespace Siglot {

std::thread::id ReceiverBase::threadId() const {
    return _thread.get_id();
}

void ReceiverBase::runInNewThread() {
    if (_thread.joinable()) {
        std::cerr << "Cannot run receiver in new thread, because it is already running in new thread" << std::endl;
        return;
    }
    _thread = std::thread{[](){SiglotCore::get()->run();}};
}

void ReceiverBase::quitThread(bool wait, bool force){
    if (_thread.joinable()) {
        std::cerr << "Cannot quit receiver thread, because it is not running in new thread" << std::endl;
        return;
    }
    SiglotCore::get()->quitThread(_thread.get_id(), force);
    if (wait) {
        _thread.join();
    } else {
        _thread.detach();
    }
}


void ReceiverBase::connectTo(SenderBase* sender) {
    Siglot::connect(sender, this);
}
    
void ReceiverBase::disconnectFromAll() {
    Siglot::disconnect(this);
}

void ReceiverBase::disconnectFrom(SenderBase* sender) {
    Siglot::disconnect(sender, this);
}

ReceiverBase::~ReceiverBase() {
    disconnectFromAll();
}

} // namespace Siglot
