#include <iostream>
#include <vector>

#include <tbc.h>
#include <tbc/sender.h>
#include <tbc/receiver.h>

constexpr int numberOfSenders = 5;
constexpr int numberOfReceivers = 7;

class IntSender : public TBC::Sender<int> {
public:
    void sendValue(int value) {
        valueSignal(value);
    }
};

class IntReceiver : public TBC::Receiver<int> {
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
    
    for (size_t i = 0; i < senders.size(); ++i) {
        senders[i].sendValue(i);
    }
    
    
    // process all signals
    int processedSignals = 0;
    const int expectedSignals = senders.size() * receivers.size();
    while (TBC::processNextSignal()) {
        ++processedSignals;
    }
    if (processedSignals != expectedSignals) {
        std::cout << "Number of signals: " << processedSignals << ", expected: " << expectedSignals << std::endl;
        return 1;
    }
    
    for (auto&& receiver : receivers) {
        auto&& returned_values = receiver.values();
        for (size_t i = 0; i < senders.size(); ++i) {
            if (returned_values[i] != static_cast<int>(i)) {
                std::cout << "Returned vector has different values:";
                for (auto&& value : returned_values) {
                    std::cout << " " << value;
                }
                std::cout << " , expected:";
                for (size_t i = 0; i < senders.size(); ++i) {
                    std::cout << " " << i;
                }
                std::cout << std::endl;
                return 1;
            }
        }
    }

    return 0;
}