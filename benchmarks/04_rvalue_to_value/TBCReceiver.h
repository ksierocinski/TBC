#ifndef TBC_BENCH_TBCRECEIVER
#define TBC_BENCH_TBCRECEIVER

#include <iostream>

#include <tbc/receiver.h>
#include "../00_common_files/Msg.h"

class TBCReceiver : public TBC::Receiver<Msg> {
public:
    void valueSlot(Msg msg) override {
        auto endTimePoint = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds> (endTimePoint - msg.sendTimePoint()).count() << ",";
    }
};

#endif // TBC_BENCH_TBCRECEIVER
