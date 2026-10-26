#ifndef ML_TIMEUTIL_H
#define ML_TIMEUTIL_H

namespace ml {
// the console's date and time in 64 bits, as ml::TimeUtil::getTime fills it from the calendar time (the field names
// are not the original's)
struct TimeInfo {
    unsigned int msec : 14;
    unsigned int sec : 6;
    unsigned int min : 6;
    unsigned int hour : 6;
    unsigned int : 0;  // the second word
    unsigned int day : 5;
    unsigned int yday : 9;  // the day of the year
    unsigned int month : 4;
    unsigned int year : 14;
};

class TimeUtil {
public:
    static bool getTime(TimeInfo& info);  // false when the calendar time is not available
};
}  // namespace ml

#endif
