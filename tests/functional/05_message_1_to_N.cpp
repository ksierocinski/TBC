#include <iostream>
#include <vector>

#include <siglot.h>
#include <siglot/sender.h>
#include <siglot/receiver.h>

constexpr int numberOfReceivers = 10;

class IntSender : public Siglot::Sender<int> {
public:
    void sendValue(int value) {
        valueSignal(value);
    }
};

class IntReceiver : public Siglot::Receiver<int> {
    std::vector<int> _values;
public:
    void valueSlot(int value) override {
        _values.push_back(value);
    }

    const std::vector<int>& values() const {
        return _values;
    }
};

int main() {
    const std::vector<int> expectedValues {-42, -1, 0, 1, 42};

    IntSender sender;
    std::vector<IntReceiver> receivers (numberOfReceivers);

    // connect and signal
    for (auto&& receiver : receivers) {
        receiver.connectTo(&sender);
    }
    
    for (auto&& value : expectedValues) {
        sender.sendValue(value);
    }
    
    // process all signals
    int processedSignals = 0;
    const int expectedSignals = receivers.size() * expectedValues.size();
    while (Siglot::processNextSignal()) {
        ++processedSignals;
    }
    if (processedSignals != expectedSignals) {
        std::cout << "Number of signals: " << processedSignals << ", expected: " << expectedSignals << std::endl;
        return 1;
    }
    
    for (auto&& receiver : receivers) {
        auto&& returnedValues = receiver.values();
        if (returnedValues != expectedValues) {
            std::cout << "Returned vector has different values:";
            for (auto&& value : returnedValues) {
                std::cout << " " << value;
            }
            std::cout << " , expected:";
            for (auto&& value : expectedValues) {
                std::cout << " " << value;
            }
            std::cout << std::endl;
            return 1;
        }
    }

    return 0;
}