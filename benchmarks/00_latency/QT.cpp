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

    std::cout << "QT latency [µs]: ";
    for (size_t i = 0; i < iterations; ++i) {
        sender.send(std::chrono::high_resolution_clock::now());
        std::this_thread::sleep_for(std::chrono::seconds{1});
    }
    std::cout << std::endl;

    newThread.quit();
    newThread.wait();

    return 0;
}
