#ifndef _TBC_RECEIVER_BASE_H
#define _TBC_RECEIVER_BASE_H

#include <mutex>
#include <thread>

namespace TBC {

/** Forward declarations */
class SenderBase;

/** Base class for all the receivers */
class ReceiverBase {
    /** Thread asssigned to the slot */
    std::thread _thread;

public:
    /** Getter for thread id of this receiver
     * 
     * \return thread id of this receiver
    */
    std::thread::id threadId() const;

    /** Runs slots of this receiver in new thread */
    void runInNewThread();

    /** Request thread to quit
     * 
     * Thread will exit when finish all queued callbacks.
     * 
     * \param wait true if current thread should wait for receiver's thread to exit, false otherwise
     * \param force false if receiver's thread should run all callbacks in queue, true otherwise
    */
    void quitThread(bool wait = false, bool force = false);

    /** Performs a connection to the sender
     *  
     * \param sender sender to connect to
     */
    void connectTo(SenderBase* sender);

    /** Performs a disconnection from the sender
     *  
     * \param sender sender to disconnect from
     */
    void disconnectFrom(SenderBase* sender);

    /** Disconnect from all connected receivers */
    void disconnectFromAll();

    /** Destructor */
    virtual ~ReceiverBase();
};

} // namespace TBC

#endif // _TBC_RECEIVER_BASE_H
