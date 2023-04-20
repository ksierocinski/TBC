#ifndef TBC_BENCH_TBCSENDER
#define TBC_BENCH_TBCSENDER

#include <tbc/sender.h>

class TBCSender : public TBC::Sender<std::chrono::high_resolution_clock::time_point> {};

#endif // TBC_BENCH_TBCSENDER
