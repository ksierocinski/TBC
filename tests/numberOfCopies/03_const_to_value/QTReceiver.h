#ifndef TBC_BENCH_QTRECEIVER
#define TBC_BENCH_QTRECEIVER

#include <iostream>
#include <thread>

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
        std::cout << "QT const& to value copies: " << msg.copyCounter() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds{1});
    }
}; 

#endif // TBC_BENCH_QTRECEIVER
