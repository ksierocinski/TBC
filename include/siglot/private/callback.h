#ifndef _SIGLOT_CALLBACK_H
#define _SIGLOT_CALLBACK_H

namespace Siglot {

class ReceiverBase;

class Callback {
protected:

    virtual void removeReceiver(ReceiverBase* receiver) = 0;
    
    virtual void trigger() = 0;
};

} // namespace Siglot

#endif
