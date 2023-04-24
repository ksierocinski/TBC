#include <chrono>

#include <tbc.h>
#include "TBCReceiver.h"
#include "TBCSender.h"


using std::chrono::high_resolution_clock;
constexpr int iterations = 50;

int main() {

    TBCSender sender;
    TBCReceiver receiver;

    receiver.runInNewThread();

    TBC::connect(&sender, &receiver);


    for (size_t msgByteSizeInKb = 1; msgByteSizeInKb <= Msg::maxMsgSizeInKb; msgByteSizeInKb*=8)
    {
        std::cout << "TBC const& to value " << msgByteSizeInKb << " kB msg [µs]: ";
        Msg data (msgByteSizeInKb);
        for (size_t i = 0; i < iterations; ++i) {
            data.resetCreationTimePoint();
            sender.valueSignal(const_cast<const Msg&>(data));
            std::this_thread::sleep_for(std::chrono::seconds{1});
        }
        std::cout << std::flush << std::endl;
    }
    
    receiver.quitThread(true);


    return 0;
}
