#ifndef TBC_BENCH_QTSENDER
#define TBC_BENCH_QTSENDER

#include <thread>

#include <QtCore>

constexpr int iterations = 10;

class QTSender : public QObject {
    Q_OBJECT
public:
    QTSender(QObject* parent = nullptr) :
        QObject(parent)
    {}

    ~QTSender() {};

public:
signals:
    void send(std::chrono::high_resolution_clock::time_point timePoint);

public slots:
    void sendSignals() {
        for (size_t i = 0; i < iterations; ++i) {
            emit send(std::chrono::high_resolution_clock::now());
            std::this_thread::sleep_for(std::chrono::seconds{1});
        }
        QCoreApplication::quit();
    }
};

Q_DECLARE_METATYPE(std::chrono::high_resolution_clock::time_point)

#endif // TBC_BENCH_QTSENDER
