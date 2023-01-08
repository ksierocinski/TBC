#ifndef _SIGLOT_CALLBACK_QUEUE_H
#define _SIGLOT_CALLBACK_QUEUE_H

#include <condition_variable>
#include <deque>
#include <mutex>
#include <thread>
#include <unordered_map>

#include "callback.h"

namespace Siglot {

/** Class responsible for queuing callbacks and calling them one by one */
class CallbackQueue {

    /** Helper class with information for each running thread */
    struct ThreadInfo {

        enum class QUIT_STATUS {
            RUN,
            QUIT,
            FORCE_QUIT
        };

        std::deque<std::unique_ptr<Callback>> callbackQueue;
        
        /** Variable to notify it when new callback is added to its empty queue */
        std::condition_variable callbackQueueCV;

        /** True when thread is running callback loop, set to false to end the loop */
        QUIT_STATUS run = QUIT_STATUS::RUN;

        /** Mutex for accessing this thread ThreadInfo object */
        std::mutex infoMutex;
    };

    /** Map thread to its ThreadInfo */
    std::unordered_map<std::thread::id, ThreadInfo> _threads;

public:
    
    /** Add callback to the thread queue 
     * 
     * \param callback callback to add to queue
    */
    void addCallback(std::unique_ptr<Callback> callback);

    /** Starts callback loop */
    void run();

    /** Request specified thread to quit
     * 
     * \param threadId thread id to quit
     * \param force false if quited thread should run all callbacks in queue, true otherwise
    */
    void quitThread(std::thread::id threadId, bool force = false);
};

} // namespace Siglot

#endif // _SIGLOT_CALLBACK_QUEUE_H
