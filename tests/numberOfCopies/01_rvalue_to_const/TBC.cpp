#include <chrono>

#include <tbc.h>
#include "TBCReceiver.h"
#include "TBCSender.h"


#include "../common_files/Msg.h"

using std::chrono::high_resolution_clock;
constexpr int iterations = 50;

int main() {

    TBCSender sender;
    TBCReceiver receiver;

    receiver.runInNewThread();

    TBC::connect(&sender, &receiver);
    
    sender.valueSignal(Msg{});
    std::this_thread::sleep_for(std::chrono::seconds{1});

    receiver.quitThread(true);

    return 0;
}
