#include <iostream>
#include <vector>

#include <siglot.h>
#include <siglot/sender.h>
#include <siglot/receiver.h>

constexpr int numberOfSenders = 5;
constexpr int numberOfReceivers = 7;

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
    std::vector<IntSender> senders (numberOfSenders);
    std::vector<IntReceiver> receivers (numberOfReceivers);

    // connect and signal
    for (auto&& sender : senders) {
        for (auto&& receiver : receivers) {
            receiver.connectTo(&sender);
        }
    }
    
    int value = 0;
    for (int i = 0; i < senders.size(); ++i) {
        senders[i].sendValue(i);
    }
    
    
    // process all signals
    int processedSignals = 0;
    const int expectedSignals = senders.size() * receivers.size();
    while (Siglot::processNextSignal()) {
        ++processedSignals;
    }
    if (processedSignals != expectedSignals) {
        std::cout << "Number of signals: " << processedSignals << ", expected: " << expectedSignals << std::endl;
        return 1;
    }
    
    for (auto&& receiver : receivers) {
        auto&& returned_values = receiver.values();
        for (int i = 0; i < senders.size(); ++i) {
            auto&& returned_values = receiver.values();
            if (returned_values[i] != i) {
                std::cout << "Returned vector has different values:";
                for (auto&& value : returned_values) {
                    std::cout << " " << value;
                }
                std::cout << " , expected:";
                for (int i = 0; i < senders.size(); ++i) {
                    std::cout << " " << i;
                }
                std::cout << std::endl;
                return 1;
            }
        }
    }

    return 0;
}