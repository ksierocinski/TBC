#ifndef TBC_BENCH_TBCRECEIVER
#define TBC_BENCH_TBCRECEIVER

#include <iostream>

#include <tbc/receiver.h>
#include "../common_files/Msg.h"

class TBCReceiver : public TBC::Receiver<Msg> {
public:
    void valueSlot(Msg msg) override {
        std::cout << "TBC const& to value copies: " << msg.copyCounter() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds{1});
    }
};

#endif // TBC_BENCH_TBCRECEIVER
