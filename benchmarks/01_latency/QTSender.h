#ifndef TBC_BENCH_QTSENDER
#define TBC_BENCH_QTSENDER

#include <thread>

#include <QtCore>

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
};

Q_DECLARE_METATYPE(std::chrono::high_resolution_clock::time_point)

#endif // TBC_BENCH_QTSENDER
