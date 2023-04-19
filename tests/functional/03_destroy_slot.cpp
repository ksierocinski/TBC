#include <iostream>

#include <tbc.h>
#include <tbc/sender.h>
#include <tbc/receiver.h>

constexpr int random_value = 42;

class IntSender : public TBC::Sender<int> {
public:
    void sendValue() {
        valueSignal(random_value);
    }
};

class IntReceiver : public TBC::Receiver<int> {

public:
    void valueSlot(int) override {}
};

int main() {
    IntSender sender;
    
    {
        IntReceiver receiver;

        // connect and signal
        TBC::connect(&sender, &receiver);
    }

    sender.sendValue();
    bool wasProcessed = TBC::processNextSignal();
    if (wasProcessed) {
        std::cout << "TBC::processNextSignal() returned: true, expected: false" << std::endl;
        return 1;
    }

    return 0;
}