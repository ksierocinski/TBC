#ifndef TBC_BENCH_QTRECEIVER
#define TBC_BENCH_QTRECEIVER

#include <iostream>

#include <QtCore>

#include "../common_files/Msg.h"

class QTReceiver : public QObject {
    Q_OBJECT
public:
    QTReceiver(QObject* parent = nullptr) :
        QObject(parent)
    {}

    ~QTReceiver() {};

public slots:
    void valueSlot(Msg msg) {
        auto endTimePoint = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds> (endTimePoint - msg.sendTimePoint()).count() << ",";
    }
}; 

#endif // TBC_BENCH_QTRECEIVER
