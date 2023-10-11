#include <chrono>

#include <QtCore>
#include <QThread>
#include "QTReceiver.h"
#include "QTSender.h"

using std::chrono::high_resolution_clock;
constexpr int iterations = 50;

int main(int argc, char** argv) {
    QCoreApplication qtApp(argc, argv);
    QTSender sender;
    QTReceiver receiver;
    QThread newThread;
    receiver.moveToThread(&newThread);

    QObject::connect(&sender, &QTSender::send, &receiver, &QTReceiver::valueSlot, Qt::QueuedConnection);
    newThread.start();

    Msg msg;
    sender.send(msg);
    std::this_thread::sleep_for(std::chrono::seconds{1});

    newThread.quit();
    newThread.wait();

    return 0;
}
