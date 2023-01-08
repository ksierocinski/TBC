#ifndef _SIGLOT_SENDER_H
#define _SIGLOT_SENDER_H

#include <utility>

#include "siglot/private/senderBase.h"
#include "siglot.h"

namespace Siglot {

/** This is the class the user object inherits from to allow
 *  connect to receivers and emit signals with T data.
 */
template <class T>
class Sender : public SenderBase {

public:
    /** Perform a signal with const reference to the data
     * 
     *  WARNING: User must ensure that reference is valid when slot is called!
     *
     * \param data const reference data to send with the signal
     */
    void constRefSignal(const T& data) {
        Siglot::constRefSignal(this, data);
    }
    
    /** Perform a signal with data
     * 
     * The data will be copied only if more that one receiver is connected
     * to the sender.
     * 
     * \param data data to send with the signal
     */
    void valueSignal(T data) {
        Siglot::valueSignal(this, std::move(data));
    }
};

} // namespace Siglot

#endif // _SIGLOT_SENDER_H
