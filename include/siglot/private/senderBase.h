#ifndef _SIGLOT_SENDER_BASE_H
#define _SIGLOT_SENDER_BASE_H

namespace Siglot {

class ReceiverBase;

class SenderBase {
public:
    void connectTo(ReceiverBase* receiver);

    void disconnectFromAll() ;

    void disconnectFrom(ReceiverBase* receiver);

    virtual ~SenderBase();
};

} // namespace Siglot

#endif
