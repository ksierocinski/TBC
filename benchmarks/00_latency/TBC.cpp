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

    
    std::cout << "TBC latency [µs]: ";
    for (size_t i = 0; i < iterations; ++i) {
        sender.valueSignal(std::chrono::high_resolution_clock::now());
        std::this_thread::sleep_for(std::chrono::seconds{1});
    }
    std::cout << std::endl;
    
    receiver.quitThread(true);


    return 0;
}
