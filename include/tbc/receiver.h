#ifndef _TBC_RECEIVER_H
#define _TBC_RECEIVER_H

#include "private/receiverBase.h"

namespace TBC {

/** This is the class the user object inherits from to allow
 *  connect to senders and receive signals with T data.
 */
template <class T>
class Receiver : public ReceiverBase {

public:
    /** Called when received a signal with const reference to the data
     * 
     *  WARNING: User (sender object) must ensure that reference is valid when slot is called!
     *
     * \param data const reference data received with the signal
     */
    virtual void constRefSlot(const T& data) {
        // do nothing by default
    }
    
    /** Called when received a signal with data
     * 
     * By default this will call constRefSlot
     * 
     * \param data data received with the signal
     */
    virtual void valueSlot(T data) {
        constRefSlot(std::move(data));
    }
};

} // namespace TBC

#endif // _TBC_RECEIVER_H
