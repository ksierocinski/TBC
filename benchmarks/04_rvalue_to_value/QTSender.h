#ifndef TBC_BENCH_QTSENDER
#define TBC_BENCH_QTSENDER

#include <iostream>
#include <thread>

#include <QtCore>

#include "../00_common_files/Msg.h"

constexpr int iterations = 5;

class QTSender : public QObject {
    Q_OBJECT
public:
    QTSender(QObject* parent = nullptr) :
        QObject(parent)
    {}

    ~QTSender() {};

public:
signals:
    void send(Msg msg);

public slots:
    void sendSignals() {
        for (size_t msgByteSizeInKb = 1; msgByteSizeInKb <= 32768; msgByteSizeInKb*=8)
        {
            std::cout << "QT rvalue to value " << msgByteSizeInKb << " kB msg [µs]: ";
            for (size_t i = 0; i < iterations; ++i) {
                emit send(Msg{msgByteSizeInKb});
                std::this_thread::sleep_for(std::chrono::seconds{1});
            }
            std::cout << std::endl;
        }
        QCoreApplication::quit();
    }
};

Q_DECLARE_METATYPE(Msg)

#endif // TBC_BENCH_QTSENDER
