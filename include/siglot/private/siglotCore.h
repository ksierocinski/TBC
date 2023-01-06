#ifndef _SIGLOT_SIGLOT_CORE_H
#define _SIGLOT_SIGLOT_CORE_H

#include <cstdint>
#include <deque>
#include <functional>
#include <memory>
#include <unordered_map>

#include "callbackQueue.h"

namespace Siglot {

class Callback;

class ReceiverBase;

class Receivers;

class SiglotCore {
    using Connections = std::unordered_map<std::uintptr_t, std::unique_ptr<Receivers>>;

    CallbackQueue _callbackQueue;
    Connections _connections;

    SiglotCore() = default;
    SiglotCore(const SiglotCore&) = delete;
    SiglotCore(SiglotCore&&) = delete;
public:        
    static SiglotCore* get();
    void run();
    void addCallback(std::unique_ptr<Callback>);
    void addConnection(std::uintptr_t sender, ReceiverBase* receiver);
    void removeConnection(std::uintptr_t sender, ReceiverBase* receiver);
    void removeConnection(std::uintptr_t sender);
    void removeConnection(ReceiverBase* receiver);

    ~SiglotCore();
};

} // namespace Siglot

#endif
