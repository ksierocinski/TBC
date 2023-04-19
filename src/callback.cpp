#include "tbc/private/receiverBase.h"

#include "tbc/private/callback.h"

namespace TBC {

std::thread::id Callback::threadId() {
    return receiver()->threadId();
}

} // namespace TBC
