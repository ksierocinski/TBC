#ifndef _SIGLOT_CALLBACK_H
#define _SIGLOT_CALLBACK_H

#include <thread>

namespace Siglot {

class ReceiverBase;

/** Base class of all callbacks */
class Callback {

public:
    /** Trigger callback*/
    virtual void trigger() = 0;

    /** Getter for receiver pointer
     * 
     * \return receiver pointer
    */
    virtual ReceiverBase* receiver() = 0;

    /** Getter for thread on which call the receiver slot
     * 
     * \return thread id on which call the receiver slot
    */
    std::thread::id threadId();
};

} // namespace Siglot

#endif // _SIGLOT_CALLBACK_H
