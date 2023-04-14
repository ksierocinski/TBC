#include <iostream>

#include <siglot.h>
#include <siglot/sender.h>
#include <siglot/receiver.h>

constexpr int random_value = 42;

class IntSender : public Siglot::Sender<int> {
public:
    void sendValue() {
        valueSignal(random_value);
    }
};

class IntReceiver : public Siglot::Receiver<int> {

public:
    void valueSlot(int) override {}
};

int main() {
    IntSender sender;
    
    {
        IntReceiver receiver;

        // connect and signal
        Siglot::connect(&sender, &receiver);
    }

    sender.sendValue();
    bool wasProcessed = Siglot::processNextSignal();
    if (wasProcessed) {
        std::cout << "Siglot::processNextSignal() returned: true, expected: false" << std::endl;
        return 1;
    }

    return 0;
}