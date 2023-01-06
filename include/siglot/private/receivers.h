#ifndef _SIGLOT_RECEIVERS_H
#define _SIGLOT_RECEIVERS_H

#include <list>
#include <memory>

#include "constRefCallback.h"
#include "valueCallback.h"

class ReceiverBase;

namespace Siglot {

class Receivers {
    
    std::list<ReceiverBase*> _receivers;

public:
    void addReceiver(ReceiverBase* receiver);
    
    void removeReceiver(ReceiverBase* receiver);

    template <class T>
    std::unique_ptr<Callback> createConstRefCallback(const T& data) const {
        return new ConstRefCallback<T>{data, std::list<Receiver<T>*>{_receivers}};
    }

    template <class T>
    std::unique_ptr<Callback> createValueCallback(T&& data) const {
        return new ValueCallback<T>{std::move(data), std::list<Receiver<T>*>{_receivers}};
    }
};

} // namespace Siglot

#endif
