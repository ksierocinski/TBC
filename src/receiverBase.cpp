#include <iostream>

#include "tbc.h"

#include "tbc/private/receiverBase.h"
#include "tbc/private/tbcCore.h"

namespace TBC {

std::thread::id ReceiverBase::threadId() const {
    if (_thread.get_id() != std::thread::id()) {
        return _thread.get_id();
    } else {
        return std::this_thread::get_id();
    }
}

void ReceiverBase::runInNewThread() {
    if (_thread.joinable()) {
        std::cerr << "Cannot run receiver in new thread, because it is already running in new thread" << std::endl;
        return;
    }
    _thread = std::thread{[this](){
        TBCCore::get()->run();
    }};
    
}

void ReceiverBase::quitThread(bool wait, bool force){
    if (_thread.joinable()) {
        TBCCore::get()->quitThread(_thread.get_id(), force);
        if (wait) {
            _thread.join();
        } else {
            _thread.detach();
        }
    }
    _thread = std::thread{};
}


void ReceiverBase::connectTo(SenderBase* sender) {
    TBC::connect(sender, this);
}
    
void ReceiverBase::disconnectFromAll() {
    TBC::disconnect(this);
}

void ReceiverBase::disconnectFrom(SenderBase* sender) {
    TBC::disconnect(sender, this);
}

ReceiverBase::~ReceiverBase() {
    disconnectFromAll();
}

} // namespace TBC
