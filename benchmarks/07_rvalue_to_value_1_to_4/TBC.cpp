#include <chrono>

#include <tbc.h>
#include "TBCReceiver.h"
#include "TBCSender.h"


#include "../00_common_files/Msg.h"

using std::chrono::high_resolution_clock;
constexpr int iterations = 50;

int main() {

    TBCSender sender;

    auto timeElapsedSptr = std::make_shared<std::vector<int>>();
    timeElapsedSptr->reserve(numberOfReceivers);
    auto timeElapsedMutexSptr = std::make_shared<std::mutex>();
    
    std::vector<TBCReceiver> receivers;
    receivers.reserve(numberOfReceivers);
    for (int i = 0; i < numberOfReceivers; ++i) {
        receivers.emplace_back(timeElapsedSptr, timeElapsedMutexSptr);
    }
    

    for (size_t i = 0; i < numberOfReceivers; ++i) {
        TBC::connect(&sender, &receivers[i]);
        receivers[i].runInNewThread();
    }


    for (size_t msgByteSizeInKb = 1; msgByteSizeInKb <= Msg::maxMsgSizeInKb; msgByteSizeInKb*=8)
    {
        std::cout << "TBC 1 to " << numberOfReceivers << " rvalue to value " << msgByteSizeInKb << " kB msg [µs]: ";
        for (size_t i = 0; i < iterations; ++i) {
            sender.valueSignal(Msg {msgByteSizeInKb});
            std::this_thread::sleep_for(std::chrono::seconds{1});
        }
        std::cout << std::flush << std::endl;
    }
    
    for (auto&& receiver : receivers) {
        receiver.quitThread(true);
    }
    

    return 0;
}
