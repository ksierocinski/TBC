#include <chrono>
#include <mutex>
#include <iostream>

#include <siglot.h>
#include <siglot/sender.h>
#include <siglot/receiver.h>

std::mutex valueMutex;

class IntSender : public Siglot::Sender<int> {
public:
    void sendValue(int value) {
        valueSignal(value);
    }
};

class IntReceiver : public Siglot::Receiver<int> {
    int _value = 0;
public:

    void valueSlot(int value) override {
        valueMutex.lock();
        _value = value;
        valueMutex.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    int value() const {
        valueMutex.lock();
        int result = _value;
        valueMutex.unlock();
        return result;
    }
};

int main() {
    IntSender sender;
    IntReceiver receiver;

    if (receiver.threadId() != std::this_thread::get_id()) {
        std::cout << "Receiver started in wrong thread" << std::endl;
        return 1;
    }

    receiver.connectTo(&sender);

    // run receiver in new thread
    receiver.runInNewThread();

    sender.sendValue(1);
    sender.sendValue(2);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    receiver.quitThread(true, true);
    // receiver should process first value, but not the second, wait to see if thread won't perform next signal
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    if (receiver.value() != 1) {
        std::cout << "Receiver returned value " << receiver.value() << ", expected: 1" << std::endl;
        return 1;
    }

    return 0;
}