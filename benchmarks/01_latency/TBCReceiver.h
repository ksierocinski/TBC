#ifndef TBC_BENCH_TBCRECEIVER
#define TBC_BENCH_TBCRECEIVER

#include <iostream>

#include <tbc/receiver.h>

class TBCReceiver : public TBC::Receiver<std::chrono::high_resolution_clock::time_point> {
public:
    void valueSlot(std::chrono::high_resolution_clock::time_point sendTimePoint) override {
        auto endTimePoint = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds> (endTimePoint - sendTimePoint).count() << ",";
    }
};

#endif // TBC_BENCH_TBCRECEIVER
