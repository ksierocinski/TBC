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
    
    QObject::connect(&sender, &QTSender::send, &receiver, &QTReceiver::constRefSlot, Qt::QueuedConnection);
    newThread.start();

    for (size_t msgByteSizeInKb = 1; msgByteSizeInKb <= Msg::maxMsgSizeInKb; msgByteSizeInKb*=8)
    {
        std::cout << "QT const& to const& " << msgByteSizeInKb << " kB msg [µs]: ";
        Msg msg {msgByteSizeInKb};
        for (size_t i = 0; i < iterations; ++i) {
            msg.resetCreationTimePoint();
            sender.send(const_cast<const Msg&>(msg));
            std::this_thread::sleep_for(std::chrono::seconds{1});
        }
        std::cout << std::endl;
    }

    newThread.quit();
    newThread.wait();

    return 0;
}
