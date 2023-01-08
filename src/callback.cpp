#include "siglot/private/receiverBase.h"

#include "siglot/private/callback.h"

namespace Siglot {

std::thread::id Callback::threadId() {
    return receiver()->threadId();
}

} // namespace Siglot
