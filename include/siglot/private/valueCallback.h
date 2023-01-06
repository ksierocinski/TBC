#ifndef _SIGLOT_VALUE_CALLBACK_H
#define _SIGLOT_VALUE_CALLBACK_H

#include <list>

#include "callback.h"
#include "../receiver.h"

namespace Siglot {

template <class T>
class ValueCallback : public Callback {
    T _data;
    std::list<Receiver<T>*> _receivers;

public:
    ValueCallback(T data, std::list<Receiver<T>*>&& receivers) :
        _data{std::move(data)},
        _receivers{std::move(receivers)}
    {}

    void removeReceiver(ReceiverBase* receiver) override {
        _receivers.remove(receiver);
    }

    void trigger() override {
        if (!_receivers.empty()) {
            const size_t lastElement = _receivers.size() - 1;
            for (size_t i = 0; i < lastElement; ++i) {
                // copy data to all apart last one
                _receivers[i]->valueSlot(_data);
            }
            // move data to last one (callback will be destroyed anyway)
            _receivers[lastElement]->valueSlot(std::move(_data));
        }
    }
};

} // namespace Siglot

#endif
