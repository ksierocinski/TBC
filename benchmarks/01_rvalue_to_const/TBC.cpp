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


    for (size_t msgByteSizeInKb = 1; msgByteSizeInKb <= Msg::maxMsgSizeInKb; msgByteSizeInKb*=8)
    {
        std::cout << "TBC rvalue to const& " << msgByteSizeInKb << " kB msg [µs]: ";
        
        for (size_t i = 0; i < iterations; ++i) {
            sender.valueSignal(Msg{ msgByteSizeInKb });
            std::this_thread::sleep_for(std::chrono::seconds{1});
        }
        std::cout << std::flush << std::endl;
    }
    
    receiver.quitThread(true);


    return 0;
}
