#ifndef _SIGLOT_SENDER_H
#define _SIGLOT_SENDER_H

#include <utility>

#include "siglot/private/senderBase.h"
#include "siglot.h"

namespace Siglot {

template <class T>
class Sender : public SenderBase {
public:
    void constRefSignal(const T& data) {
        Siglot::constRefSignal(this, data);
    }
    
    void valueSignal(T data) {
        Siglot::valueSignal(this, std::move(data));
    }

    ~Sender() override = default;
};

} // namespace Siglot

#endif
