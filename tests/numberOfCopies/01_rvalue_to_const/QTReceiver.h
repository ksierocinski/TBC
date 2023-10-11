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
    void constRefSlot(const Msg& msg) {
        std::cout << "QT rvalue to const& copies: " << msg.copyCounter() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds{1});
    }
}; 

#endif // TBC_BENCH_QTRECEIVER
