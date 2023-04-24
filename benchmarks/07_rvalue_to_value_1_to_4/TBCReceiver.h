#ifndef TBC_BENCH_TBCRECEIVER
#define TBC_BENCH_TBCRECEIVER

#include <algorithm>
#include <iostream>
#include <memory>
#include <mutex>

#include <tbc/receiver.h>
#include "../00_common_files/Msg.h"

constexpr int numberOfReceivers = 4;

class TBCReceiver : public TBC::Receiver<Msg> {
    std::shared_ptr<std::vector<int>> _timeElapsedSptr;
    std::shared_ptr<std::mutex> _timeElapsedMutexSptr;

public:
    TBCReceiver(std::shared_ptr<std::vector<int>> timeElapsedSptr, std::shared_ptr<std::mutex> timeElapsedMutexSptr) :
        _timeElapsedSptr(std::move(timeElapsedSptr)),
        _timeElapsedMutexSptr(std::move(timeElapsedMutexSptr))
    {}

    TBCReceiver(const TBCReceiver& ) = delete;

    TBCReceiver(TBCReceiver&& other) {
        _timeElapsedSptr = std::move(other._timeElapsedSptr);
        _timeElapsedMutexSptr = std::move(other._timeElapsedMutexSptr);
    }

    void valueSlot(Msg msg) override {
        auto endTimePoint = std::chrono::high_resolution_clock::now();
        
        std::lock_guard<std::mutex> lock_mutex(*_timeElapsedMutexSptr);
        _timeElapsedSptr->push_back(std::chrono::duration_cast<std::chrono::microseconds> (endTimePoint - msg.sendTimePoint()).count());
        if (_timeElapsedSptr->size() == numberOfReceivers) {
            auto it = std::max_element(_timeElapsedSptr->begin(), _timeElapsedSptr->end());
            std::cout << *it << ",";
            _timeElapsedSptr->clear();
        }
    }
};

#endif // TBC_BENCH_TBCRECEIVER
