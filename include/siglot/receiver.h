#ifndef _SIGLOT_RECEIVER_H
#define _SIGLOT_RECEIVER_H

#include "private/receiverBase.h"

namespace Siglot {

template <class T>
class Receiver : public ReceiverBase {
public:
    virtual void constRefSlot(const T& data) {
        // do nothing by default
    }
    
    virtual void valueSlot(T data) {
        constRefSlot(std::move(data));
    }
};

} // namespace Siglot

#endif
