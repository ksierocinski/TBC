#include <iostream>
#include <thread>
#include <vector>

#include <siglot.h>
#include <siglot/sender.h>
#include <siglot/receiver.h>

std::mutex receiverMutex;

class IntSender : public Siglot::Sender<std::thread::id> {
public:
    void sendValue(std::thread::id threadId) {
        valueSignal(threadId);
    }
};

class IntReceiver : public Siglot::Receiver<std::thread::id> {
    int _numberOfProcessedSignal = 0;
    bool _receivedCorrectThreadId = false;
    std::condition_variable _processedSignalCV;
public:

    
    void valueSlot(std::thread::id threadId) override {
        {
            std::lock_guard<std::mutex> lock_mutex {receiverMutex};
            ++_numberOfProcessedSignal;
            _receivedCorrectThreadId = std::this_thread::get_id() == threadId;
        }
        _processedSignalCV.notify_one();
    }

    int numberOfProcessedSignal() const {
        return _numberOfProcessedSignal;
    }

    bool receivedCorrectThreadId() const {
        return _receivedCorrectThreadId;
    }

    std::condition_variable& processedSignalCV() {
        return _processedSignalCV;
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
    sender.sendValue(std::this_thread::get_id());
    Siglot::processNextSignal();
    if (!receiver.receivedCorrectThreadId()) {
        std::cout << "Receiver runs in wrong thread on first signal" << std::endl;
        return 1;
    }

    // run receiver in new thread and try again
    std::cout << receiver.threadId() << std::endl;
    receiver.runInNewThread();
    std::cout << receiver.threadId() << std::endl;

    {
        std::unique_lock<std::mutex> lock_mutex {receiverMutex};
        sender.sendValue(receiver.threadId());
        receiver.processedSignalCV().wait(lock_mutex, [&receiver]{return receiver.numberOfProcessedSignal() == 2;});
    }

    if (!receiver.receivedCorrectThreadId()) {
        std::cout << "Receiver runs in wrong thread on the second signal" << std::endl;
        return 1;
    }
    
    std::cout << receiver.threadId() << std::endl;
    receiver.quitThread(true);
    std::cout << receiver.threadId() << std::endl;


    sender.sendValue(std::this_thread::get_id());
    Siglot::processNextSignal();
    if (!receiver.receivedCorrectThreadId()) {
        std::cout << "Receiver runs in wrong thread on third signal" << std::endl;
        return 1;
    }

    return 0;
}