#include "siglot/private/callbackQueue.h"

namespace Siglot {

    // void CallbackQueuetryToWakeUpThread(std::thread::id threadId);

    //void CallbackQueueaddCallback(std::thread::id threadId, std::unique_ptr<Callback> callback);
void CallbackQueue::addCallback(std::unique_ptr<Callback> callback)
{

}

void CallbackQueue::callbackLoop()
{

}


} // namespace Siglot
