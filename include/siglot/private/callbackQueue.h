#ifndef _SIGLOT_CALLBACK_QUEUE_H
#define _SIGLOT_CALLBACK_QUEUE_H

#include <condition_variable>
#include <deque>
#include <thread>
#include <unordered_map>

#include "callback.h"

namespace Siglot {

class CallbackQueue {
    // std::unordered_map<std::thread::id, std::deque<std::unique_ptr<Callback>>> _callbackQueue;
    // std::unordered_map<std::thread::id, std::condition_variable> _conditionVariables;

    // void tryToWakeUpThread(std::thread::id threadId);

public:
    //void addCallback(std::thread::id threadId, std::unique_ptr<Callback> callback);
    void addCallback(std::unique_ptr<Callback> callback);
    void callbackLoop();
};

} // namespace Siglot

#endif
