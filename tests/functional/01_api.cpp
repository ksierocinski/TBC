#include <siglot.h>
#include <siglot/sender.h>
#include <siglot/receiver.h>

class IntSender : public Siglot::Sender<int> {
public:
    void sendValue(int value) {
        valueSignal(value);
    }

    void sendconstRef(const int& ref) {
        constRefSignal(ref);
    }
};

class IntReceiver : public Siglot::Receiver<int> {
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

    Siglot::connect(&sender, &receiver);
    Siglot::disconnect(&sender, &receiver);
    Siglot::disconnect(&sender);
    Siglot::disconnect(&receiver);

    return 0;
}