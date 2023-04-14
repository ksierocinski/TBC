#include <iostream>

#include "siglot.h"

#include "siglot/private/receiverBase.h"
#include "siglot/private/siglotCore.h"

namespace Siglot {

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
        SiglotCore::get()->run();
        std::cout << "Thread " << std::this_thread::get_id() << " finished" << std::endl;
    }};
    
}

void ReceiverBase::quitThread(bool wait, bool force){
    if (_thread.joinable()) {
        std::cout << "Thread " << _thread.get_id() << " is joinable, quit thread" << std::endl;
        SiglotCore::get()->quitThread(_thread.get_id(), force);
        if (wait) {
            _thread.join();
        } else {
            _thread.detach();
        }
    }
    _thread = std::thread{};
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
