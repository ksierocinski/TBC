#include <chrono>

#include <QtCore>
#include <QThread>
#include "QTReceiver.h"
#include "QTSender.h"

int main(int argc, char** argv) {
    QCoreApplication qtApp(argc, argv);
    QTSender sender;
    QTReceiver receiver;
    QThread newThread;
    receiver.moveToThread(&newThread);
    
    QObject::connect(&sender, &QTSender::send, &receiver, &QTReceiver::constRefSlot, Qt::QueuedConnection);
    newThread.start();

    sender.send(Msg{});
    std::this_thread::sleep_for(std::chrono::seconds{1});

    newThread.quit();
    newThread.wait();

    return 0;
}
