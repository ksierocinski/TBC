#ifndef TBC_COPY_MSG
#define TBC_COPY_MSG

namespace
{
    static int copyCounter = 0;
}


class Msg {
public:
    Msg() = default;

    Msg(const Msg&) {
        ++::copyCounter;
    }

    Msg(Msg&&) = default;

    int copyCounter() const {
        return ::copyCounter;
    }
}; 

#endif // TBC_COPY_MSG
