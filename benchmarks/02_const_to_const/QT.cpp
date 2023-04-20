#include <chrono>

#include <QtCore>
#include <QThread>
#include "QTReceiver.h"
#include "QTSender.h"

using std::chrono::high_resolution_clock;

int main(int argc, char** argv) {
    QCoreApplication qtApp(argc, argv);
    QTSender sender;
    QTReceiver* receiver = new QTReceiver;

    QThread newThread;
    receiver->moveToThread(&newThread);
    QObject::connect(&newThread, &QThread::finished, receiver, &QObject::deleteLater);
    QObject::connect(&sender, &QTSender::send, receiver, &QTReceiver::constRefSlot, Qt::QueuedConnection);
    newThread.start();

    QTimer::singleShot(0, &sender, &QTSender::sendSignals);

    qtApp.exec();

    newThread.quit();
    newThread.wait();

    return 0;
}
