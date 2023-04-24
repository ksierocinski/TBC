#ifndef TBC_BENCH_QTSENDER
#define TBC_BENCH_QTSENDER

#include <iostream>
#include <thread>

#include <QtCore>

#include "../00_common_files/Msg.h"

class QTSender : public QObject {
    Q_OBJECT
public:
    QTSender(QObject* parent = nullptr) :
        QObject(parent)
    {}

    ~QTSender() {};

public:
signals:
    void send(const Msg& msg);
};

Q_DECLARE_METATYPE(Msg)

#endif // TBC_BENCH_QTSENDER
