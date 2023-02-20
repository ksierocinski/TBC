#include <iostream>

#include "siglot/private/callbackQueue.h"

namespace Siglot {

void CallbackQueue::addCallback(std::unique_ptr<Callback> callback) {
    auto threadId = callback->threadId();
    ThreadInfo& threadInfo = _threads[callback->threadId()];
    
    // lock it before adding new element
    std::unique_lock<std::mutex> lock(threadInfo.infoMutex);
    threadInfo.callbackQueue.push_back(std::move(callback));
    if (threadInfo.callbackQueue.size() == 1) {
        // queue was empty -> notify thread that it has job to do
        threadInfo.callbackQueueCV.notify_one();
    }
}

bool CallbackQueue::processNextCallback()
{
    // add this thread to the map of threads
    auto threadId = std::this_thread::get_id();
    ThreadInfo& thisThead = _threads[std::this_thread::get_id()];

    std::unique_lock<std::mutex> infoLock(thisThead.infoMutex);
    if (thisThead.callbackQueue.empty()) {
        return false;
    } else {
        // trigger the callback and remove it from queue
        thisThead.callbackQueue.front()->trigger();
        thisThead.callbackQueue.pop_front();
        return true;
    }
}

void CallbackQueue::run() {
    // add this thread to the map of threads
    ThreadInfo& thisThead = _threads[std::this_thread::get_id()];

    std::unique_lock<std::mutex> infoLock(thisThead.infoMutex);
    while (true) {
        if (thisThead.callbackQueue.empty()) {
            // check if quit request occured
            if (thisThead.run != ThreadInfo::QUIT_STATUS::RUN) {
                _threads.erase(std::this_thread::get_id());
                return;
            }
            
            thisThead.callbackQueueCV.wait(infoLock, [&thisThead]{return !thisThead.callbackQueue.empty();});
            // condition variable will unlock the infoLock
        } else {
            infoLock.unlock();
        }

        // check if force quit request occured
        if ((thisThead.callbackQueue.empty() && thisThead.run == ThreadInfo::QUIT_STATUS::QUIT) ||
             thisThead.run == ThreadInfo::QUIT_STATUS::FORCE_QUIT) {
            // remove this thread from the map of threads
            _threads.erase(std::this_thread::get_id());
            return;
        }

        // trigger the callback and remove it from queue
        thisThead.callbackQueue.front()->trigger();
        infoLock.lock();
        thisThead.callbackQueue.pop_front();
    }
}

void CallbackQueue::quitThread(std::thread::id threadId, bool force)
{
    auto it = _threads.find(threadId);
    if (it == _threads.end()) {
        std::cout << "Cannot quit thread, it is not listed in running threads" << std::endl;
        return;
    }

    std::lock_guard<std::mutex> lock(it->second.infoMutex);
    if (force) {
        it->second.run = ThreadInfo::QUIT_STATUS::FORCE_QUIT;
    } else {
        it->second.run = ThreadInfo::QUIT_STATUS::QUIT;
    }

    if (it->second.callbackQueue.size() == 0) {
        // queue was empty -> notify thread that it has to quit
        it->second.callbackQueueCV.notify_one();
    }
}

} // namespace Siglot
