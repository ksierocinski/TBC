#ifndef _SIGLOT_VALUE_CALLBACK_H
#define _SIGLOT_VALUE_CALLBACK_H

#include "callback.h"
#include "../receiver.h"

namespace Siglot {

/** Callback with value as a parameter */
template <class T>
class ValueCallback : public Callback {
    /** Data of the callback given to the slot*/
    T _data;

    /** Receiver on which slot will be called */
    Receiver<T>* _receiver;

public:
    /** Constructor
     * 
     * \param data data to pass to the slots
     * \param receiver receiver of the callback
    */
    ValueCallback(T data, Receiver<T>* receiver) :
        _data{std::move(data)},
        _receiver{receiver}
    {}

    /** Trigger callback  */
    void trigger() override {
        _receiver->valueSlot(std::move(_data));
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

#endif // _SIGLOT_VALUE_CALLBACK_H
