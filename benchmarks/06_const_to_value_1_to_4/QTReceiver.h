#ifndef TBC_BENCH_QTRECEIVER_1_to_4
#define TBC_BENCH_QTRECEIVER_1_to_4

#include <algorithm>
#include <iostream>
#include <memory>
#include <mutex>

#include <QtCore>
#include "../common_files/Msg.h"

constexpr int numberOfReceivers = 4;

class QTReceiver : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(QTReceiver)

    std::shared_ptr<std::vector<int>> _timeElapsedSptr;
    std::shared_ptr<std::mutex> _timeElapsedMutexSptr;

public:
    QTReceiver(QObject* parent = nullptr) :
        QObject(parent)
    {}
    
    QTReceiver(QObject* parent, std::shared_ptr<std::vector<int>> timeElapsedSptr, std::shared_ptr<std::mutex> timeElapsedMutexSptr) :
        QObject(parent),
        _timeElapsedSptr(std::move(timeElapsedSptr)),
        _timeElapsedMutexSptr(std::move(timeElapsedMutexSptr))
    {}
    
    QTReceiver(QTReceiver&& other) {
        _timeElapsedSptr = std::move(other._timeElapsedSptr);
        _timeElapsedMutexSptr = std::move(other._timeElapsedMutexSptr);
    }

    ~QTReceiver() {};

public slots:
    void valueSlot(Msg msg) {
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

#endif // TBC_BENCH_QTRECEIVER_1_to_4
