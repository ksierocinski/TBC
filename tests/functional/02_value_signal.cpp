#include <iostream>

#include <tbc.h>
#include <tbc/sender.h>
#include <tbc/receiver.h>

constexpr int expected_value = 42;

class IntSender : public TBC::Sender<int> {
public:
    void sendValue() {
        valueSignal(expected_value);
    }
};

class IntReceiver : public TBC::Receiver<int> {
    int _value;
public:
    void valueSlot(int value) override {
        _value = value;
    }

    int value() const {
        return _value;
    }
};

int main() {
    IntSender sender;
    IntReceiver receiver;

    // connect and signal
    TBC::connect(&sender, &receiver);
    sender.sendValue();
    
    // process the signal
    bool wasProcessed = TBC::processNextSignal();
    if (!wasProcessed) {
        std::cout << "TBC::processNextSignal() returned: false, expected: true" << std::endl;
        return 1;
    }
    
    // check if signal triggered the slot
    if (receiver.value() != expected_value) {
        std::cout << "receiver.value() returned: " << receiver.value() << ", expected: " << expected_value << std::endl;
        return 1;
    }

    // check if only one signal was emmited
    wasProcessed = TBC::processNextSignal();
    if (wasProcessed) {
        std::cout << "TBC::processNextSignal() returned: true, expected: false" << std::endl;
        return 1;
    }

    // check if disconnected signal won't trigger the slot
    TBC::disconnect(&sender, &receiver);
    sender.sendValue();
    wasProcessed = TBC::processNextSignal();
    if (wasProcessed) {
        std::cout << "TBC::processNextSignal() returned: true, expected: false" << std::endl;
        return 1;
    }

    return 0;
}