#include <iostream>

#include "tbc/private/callbackQueue.h"

namespace TBC {

void CallbackQueue::triggerNextCallback(ThreadInfo& threadInfo, std::unique_lock<std::mutex>& infoLock)
{
    infoLock.unlock();
    threadInfo.callbackQueue.front()->trigger();
    infoLock.lock();
    threadInfo.callbackQueue.pop_front();
}

void CallbackQueue::prepareToThreadExit()
{
    _threadsMapMutex.lock();
    _threads.erase(std::this_thread::get_id());
    _threadsMapMutex.unlock();
}

CallbackQueue::ThreadInfo& CallbackQueue::getThreadInfo(std::thread::id threadId)
{
    _threadsMapMutex.lock();
    ThreadInfo& threadInfo = _threads[threadId];
    _threadsMapMutex.unlock();
    return threadInfo;
}

void CallbackQueue::addCallback(std::unique_ptr<Callback> callback) {
    ThreadInfo& threadInfo = getThreadInfo(callback->threadId());
    
    // lock it before adding new element
    std::unique_lock<std::mutex> lock(threadInfo.infoMutex);
    threadInfo.callbackQueue.push_back(std::move(callback));
    if (threadInfo.callbackQueue.size() == 1) {
        // queue was empty -> notify thread that it has job to do
        lock.unlock();
        threadInfo.callbackQueueCV.notify_one();
        lock.lock();
    }
}

bool CallbackQueue::processNextCallback()
{
    ThreadInfo& thisThread = getThreadInfo(std::this_thread::get_id());

    std::unique_lock<std::mutex> infoLock(thisThread.infoMutex);
    if (thisThread.callbackQueue.empty()) {
        return false;
    } else {
        triggerNextCallback(thisThread, infoLock);
        return true;
    }
}


void CallbackQueue::run()
{
    ThreadInfo& thisThread = getThreadInfo(std::this_thread::get_id());

    std::unique_lock<std::mutex> infoLock(thisThread.infoMutex);
    while (true) {
        if (thisThread.callbackQueue.empty()) {
            // check if quit request occured
            if (thisThread.run != ThreadInfo::QUIT_STATUS::RUN) {
                prepareToThreadExit();
                return;
            }
            
            thisThread.callbackQueueCV.wait(infoLock, [&thisThread]{
                return !thisThread.callbackQueue.empty() || thisThread.run != ThreadInfo::QUIT_STATUS::RUN;
            });
        }

        // check if quit request occured
        if (thisThread.callbackQueue.empty() || thisThread.run == ThreadInfo::QUIT_STATUS::FORCE_QUIT) {
            prepareToThreadExit();
            return;
        }

        triggerNextCallback(thisThread, infoLock);
    }
}

void CallbackQueue::quitThread(std::thread::id threadId, bool force)
{
    _threadsMapMutex.lock();
    auto it = _threads.find(threadId);
    _threadsMapMutex.unlock();
    if (it == _threads.end()) {
        std::cerr << "Cannot quit thread, it is not listed in running threads" << std::endl;
        return;
    }

    std::unique_lock<std::mutex> lock(it->second.infoMutex);
    if (force) {
        it->second.run = ThreadInfo::QUIT_STATUS::FORCE_QUIT;
    } else {
        it->second.run = ThreadInfo::QUIT_STATUS::QUIT;
    }

    if (it->second.callbackQueue.size() == 0) {
        // queue was empty -> notify thread that it has to quit
        lock.unlock();
        it->second.callbackQueueCV.notify_one();
        lock.lock();
    }
}

} // namespace TBC
