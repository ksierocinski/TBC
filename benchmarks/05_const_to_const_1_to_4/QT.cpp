#include <array>
#include <chrono>
#include <memory>

#include <QtCore>
#include <QThread>
#include "QTReceiver.h"
#include "QTSender.h"

using std::chrono::high_resolution_clock;
constexpr int iterations = 50;

int main(int argc, char** argv) {
    QCoreApplication qtApp(argc, argv);
    QTSender sender;
    
    auto timeElapsedSptr = std::make_shared<std::vector<int>>();
    timeElapsedSptr->reserve(numberOfReceivers);
    auto timeElapsedMutexSptr = std::make_shared<std::mutex>();

    std::vector<QTReceiver> receivers;
    receivers.reserve(numberOfReceivers);
    for (int i = 0; i < numberOfReceivers; ++i) {
        receivers.emplace_back(nullptr, timeElapsedSptr, timeElapsedMutexSptr);
    }

    std::array<QThread, numberOfReceivers> newThreads;
    for (size_t i = 0; i < numberOfReceivers; ++i) {
        receivers[i].moveToThread(&newThreads[i]);
        QObject::connect(&sender, &QTSender::send, &receivers[i], &QTReceiver::constRefSlot, Qt::QueuedConnection);
        newThreads[i].start();
    }

    for (size_t msgByteSizeInKb = 1; msgByteSizeInKb <= Msg::maxMsgSizeInKb; msgByteSizeInKb*=8)
    {
        std::cout << "QT 1 to " << numberOfReceivers << " const& to const& " << msgByteSizeInKb << " kB msg [µs]: ";
        Msg msg {msgByteSizeInKb};
        for (size_t i = 0; i < iterations; ++i) {
            msg.resetCreationTimePoint();
            sender.send(const_cast<const Msg&>(msg));
            std::this_thread::sleep_for(std::chrono::seconds{1});
        }
        std::cout << std::endl;
    }

    for (auto&& newThread : newThreads) {
        newThread.quit();
        newThread.wait();
    }

    return 0;
}
