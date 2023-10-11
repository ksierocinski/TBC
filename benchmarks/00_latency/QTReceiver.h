#ifndef TBC_BENCH_QTRECEIVER
#define TBC_BENCH_QTRECEIVER

#include <iostream>

#include <QtCore>



class QTReceiver : public QObject {
    Q_OBJECT
public:
    QTReceiver(QObject* parent = nullptr) :
        QObject(parent)
    {}

    ~QTReceiver() {};

public slots:
    void valueSlot(std::chrono::high_resolution_clock::time_point sendTimePoint) {
        auto endTimePoint = std::chrono::high_resolution_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::microseconds> (endTimePoint - sendTimePoint).count() << ",";
    }
}; 

#endif // TBC_BENCH_QTRECEIVER
