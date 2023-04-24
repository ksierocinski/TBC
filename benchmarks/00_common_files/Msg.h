#ifndef TBC_BENCH_MSG
#define TBC_BENCH_MSG

#include <chrono>
#include <vector>

constexpr int power(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    return result;
}

class Msg {
    std::vector<uint8_t> _data;
    std::chrono::high_resolution_clock::time_point _msgCreationTimePoint;
    
    

public:
    Msg() = default;

    Msg(size_t msgByteSizeInKb) :
        _data(msgByteSizeInKb * 1024),
        _msgCreationTimePoint{std::chrono::high_resolution_clock::now()}
    {}

    Msg(const Msg& other) = default;

    Msg(Msg&& other) = default;

    void resetCreationTimePoint() {
        _msgCreationTimePoint = std::chrono::high_resolution_clock::now();
    }

    const std::chrono::high_resolution_clock::time_point& sendTimePoint() const {
        return _msgCreationTimePoint;
    }

    size_t dataSizeInKb() {
        return _data.size() / 1024;
    }

    static constexpr int maxMsgSizeInKb = power(8, 6);
}; 

#endif // TBC_BENCH_MSG
