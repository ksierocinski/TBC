#include <tbc.h>
#include <tbc/sender.h>
#include <tbc/receiver.h>

class IntSender : public TBC::Sender<int> {
public:
    void sendValue(int value) {
        valueSignal(value);
    }

    void sendconstRef(const int& ref) {
        constRefSignal(ref);
    }
};

class IntReceiver : public TBC::Receiver<int> {
public:
    void constRefSlot(const int& ref) override {}
    
    void valueSlot(int value) override {}
};

int main() {
    IntSender sender;
    IntReceiver receiver;
    int value = 42;
    const int& ref = value;

    sender.connectTo(&receiver);
    sender.valueSignal(value);
    sender.constRefSignal(value);
    sender.disconnectFrom(&receiver);
    sender.disconnectFromAll();

    
    receiver.valueSlot(value);
    receiver.constRefSlot(ref);
    receiver.disconnectFrom(&sender);
    receiver.disconnectFromAll();

    TBC::connect(&sender, &receiver);
    TBC::disconnect(&sender, &receiver);
    TBC::disconnect(&sender);
    TBC::disconnect(&receiver);

    return 0;
}