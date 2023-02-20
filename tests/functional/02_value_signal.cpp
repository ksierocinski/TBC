#include <iostream>

#include <siglot.h>
#include <siglot/sender.h>
#include <siglot/receiver.h>

constexpr int expected_value = 42;

class IntSender : public Siglot::Sender<int> {
public:
    void sendValue() {
        valueSignal(expected_value);
    }
};

class IntReceiver : public Siglot::Receiver<int> {
    int _value;
public:
    void valueSlot(int value) override {
        _value = value;
    }

    int value() {
        return _value;
    }
};

int main() {
    IntSender sender;
    IntReceiver receiver;

    // connect and signal
    Siglot::connect(&sender, &receiver);
    sender.sendValue();
    
    // process the signal
    bool wasProcessed = Siglot::processNextSignal();
    if (!wasProcessed) {
        std::cout << "Siglot::processNextSignal() returned: false, expected: true" << std::endl;
        return 1;
    }
    
    // check if signal triggered the slot
    if (receiver.value() != expected_value) {
        std::cout << "receiver.value() returned: " << receiver.value() << ", expected: " << expected_value << std::endl;
        return 1;
    }

    // check if only one signal was emmited
    wasProcessed = Siglot::processNextSignal();
    if (wasProcessed) {
        std::cout << "Siglot::processNextSignal() returned: true, expected: false" << std::endl;
        return 1;
    }

    // check if disconnected signal won't trigger the slot
    Siglot::disconnect(&sender, &receiver);
    sender.sendValue();
    wasProcessed = Siglot::processNextSignal();
    if (wasProcessed) {
        std::cout << "Siglot::processNextSignal() returned: true, expected: false" << std::endl;
        return 1;
    }

    return 0;
}