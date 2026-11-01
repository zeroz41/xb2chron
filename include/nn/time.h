#ifndef NN_TIME_H
#define NN_TIME_H

#include "nn/result.h"

namespace nn { namespace time {
// the SDK's time library (ml::DeviceNx::initializeSDK starts it, ~DeviceNx ends it)
void Initialize();
void Finalize();

// the SDK's types and calls ml::TimeUtil::getTime uses (NintendoSDK's names)
struct PosixTime {
    long value;
};
struct CalendarTime {
    short year;
    signed char month;
    signed char day;
    signed char hour;
    signed char minute;
    signed char second;
};
struct TimeZone {
    char standardTimeName[8];
    bool isDaylightSavingTime;
    int utcOffsetSeconds;
};
struct CalendarAdditionalInfo {
    int dayOfWeek;
    int yearDay;
    TimeZone timeZone;
};
class StandardUserSystemClock {
public:
    static Result GetCurrentTime(PosixTime* time);
};
Result ToCalendarTime(CalendarTime* calendar, CalendarAdditionalInfo* info, const PosixTime& time);
}}  // namespace nn::time

#endif
