#ifndef _SIGLOT_SIGLOT_CORE_H
#define _SIGLOT_SIGLOT_CORE_H

#include <cstdint>
#include <deque>
#include <functional>
#include <list>
#include <memory>
#include <unordered_map>

#include "callbackQueue.h"
#include "constRefCallback.h"
#include "valueCallback.h"

namespace Siglot {

/** Forward declarations */
class Callback;
class ReceiverBase;
class Receivers;
class SenderBase;

/** Core of the library logix. It handles connections and callbacks */
class SiglotCore {
    /** Map sender pointer value to its receivers */
    using Connections = std::unordered_map<std::uintptr_t, std::list<ReceiverBase*>>;

    /** Stores all callbacks in queue and takes care of multithreading */
    CallbackQueue _callbackQueue;

    /** Stores all connections from sender to receivers*/
    Connections _connections;

    /** Constructor */
    SiglotCore() = default;

    /** Copy constructor */
    SiglotCore(const SiglotCore&) = delete;

    /** Move onstructor */
    SiglotCore(SiglotCore&&) = delete;

public:
    /** Return SiglotCore instance (singleton pattern)
     * 
     * \return pointer to SiglotCore instance
     */
    static SiglotCore* get();

    /** Start the signal slot endless loop */
    void run();

    /** Process next signal
     * 
     * \return true if signal was prcessed, false if queue was empty
    */
    bool processNextSignal();

    /** Request specified thread to quit
     * 
     * \param threadId thread id to quit
     * \param force false if quited thread should run all callbacks in queue, true otherwise
    */
    void quitThread(std::thread::id threadId, bool force = false);

    /** Add new connection between sender and receiver
     * 
     * \param sender sender to connect with receiver
     * \param receiver receiver to connect with sender
     */
    void addConnection(std::uintptr_t sender, ReceiverBase* receiver);

    /** Remove connection between sender and receiver
     * 
     * \param sender sender to disconnect with receiver
     * \param receiver receiver to disconnect with sender
     */
    void removeConnection(std::uintptr_t sender, ReceiverBase* receiver);

    /** Remove all connection of the given sender
     * 
     * \param sender sender pointer value for remove all connection
    */
    void removeConnection(std::uintptr_t sender);

    /** Remove all connection of the given receiver
     * 
     * \param receiver receiver pointer to remove all connection
    */
    void removeConnection(ReceiverBase* receiver);


    /** Add new callback to queue (created from signal) 
     * 
     * \param callback new callback to add to queue
     * \param data const reference to data to send
     */
    template <class T>
    void addConstRefCallback(std::uintptr_t sender, const T& data) {
        for (auto&& receiver : _connections[sender]) {
            std::unique_ptr<Callback> newCallback {new ConstRefCallback<T>{data, dynamic_cast<Receiver<T>*>(receiver)}};
            _callbackQueue.addCallback(std::move(newCallback));
        }
    }

    /** Add new callback to queue (created from signal) 
     * 
     * \param callback new callback to add to queue
     * \param data data value to send
     */
    template <class T>
    void addValueCallback(std::uintptr_t sender, T data) {
        std::list<ReceiverBase*>& receivers = _connections[sender];
        if (receivers.empty()) {
            return;
        }
        
        auto receiversIterator = receivers.begin();
        const size_t lastReceiverIndex = receivers.size() - 1;
        for (size_t i = 0; i < lastReceiverIndex; ++i) {
            // copy data for all but last one
            std::unique_ptr<Callback> newCallback {new ValueCallback<T>{data, dynamic_cast<Receiver<T>*>(*receiversIterator)}};
            _callbackQueue.addCallback(std::move(newCallback));
            ++receiversIterator;
        }

        // move data to the last one
        std::unique_ptr<Callback> newCallback {new ValueCallback<T>{std::move(data), dynamic_cast<Receiver<T>*>(*receiversIterator)}};
        _callbackQueue.addCallback(std::move(newCallback));
    }
};

} // namespace Siglot

#endif // _SIGLOT_SIGLOT_CORE_H
