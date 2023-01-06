#ifndef _SIGLOT_CONST_REF_CALLBACK_H
#define _SIGLOT_CONST_REF_CALLBACK_H

#include <list>

#include "../receiver.h"

namespace Siglot {

template <class T>
class ConstRefCallback {
    const T& _data;
    std::list<Receiver<T>*> _receivers;

public:
    ConstRefCallback(const T& data, std::list<Receiver<T>*>&& receivers) :
        _data{data},
        _receivers{std::move(receivers)}
    {}

    void removeReceiver(ReceiverBase* receiver) override {
        _receivers.remove(receiver);
    }

    void trigger() override {
        if (!_receivers.empty()) {
            // give a hit to compliler that size won't change
            const size_t numberOfReceivers = _receivers.size();
            for (size_t i = 0; i < numberOfReceivers; ++i) {
                _receivers[i]->constRefSlot(_data);
            }
        }
    }
};

} // namespace Siglot

#endif
