#ifndef _SIGLOT_RECEIVER_BASE_H
#define _SIGLOT_RECEIVER_BASE_H

// #include <thread>

namespace Siglot {

class SenderBase;

class ReceiverBase {
    // std::thread::id _threadId;

public:
    // std::thread::id threadId() const;

    // void runInNewThread();

    // void quitThread();

    void connectTo(SenderBase* sender);

    void disconnectFromAll();

    void disconnectFrom(SenderBase* sender);

    virtual ~ReceiverBase();
};

} // namespace Siglot

#endif
