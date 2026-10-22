#ifndef ML_TIMECOUNT_H
#define ML_TIMECOUNT_H

namespace ml {

// monolib's stopwatch (ml/Scn.cpp's range): start keeps ml::DevClock::getClockNow, getSecLap the seconds since
class TimeCount {
public:
    void start();
    float getSecLap() const;

    long pad_0;  // the clock start() keeps
};

}  // namespace ml

#endif
