#ifndef _SIGLOT_CONST_REF_CALLBACK_H
#define _SIGLOT_CONST_REF_CALLBACK_H

#include "callback.h"
#include "../receiver.h"

namespace Siglot {

/** Callback with const refence as a parameter */
template <class T>
class ConstRefCallback : public Callback {
    /** Data of the callback given to the slot*/
    const T& _data;

    /** Receiver on which slot will be called */
    Receiver<T>* _receiver;

public:
    /** Constructor
     * 
     * \param data data to pass to the slots
     * \param receiver receiver of the callback
    */
    ConstRefCallback(const T& data, Receiver<T>* receiver) :
        _data{data},
        _receiver{receiver}
    {}

    /** Trigger callback */
    void trigger() override {
        _receiver->constRefSlot(_data);
    }

    /** Getter for receiver pointer
     * 
     * \return receiver pointer
    */
    ReceiverBase* receiver() override {
        return _receiver;
    }
};

} // namespace Siglot

#endif // _SIGLOT_CONST_REF_CALLBACK_H
