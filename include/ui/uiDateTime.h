#ifndef UI_UIDATETIME_H
#define UI_UIDATETIME_H

namespace ui {

// a date and time in 64 bits, as GfMenuAdapter::setTime hands its fields to a UIObjectTimePlugin's setters
struct uiDateTime {
    unsigned long long year : 13;
    unsigned long long month : 4;
    unsigned long long pad_17 : 9;
    unsigned long long day : 5;
    unsigned long long hour : 7;
    unsigned long long minute : 7;
    unsigned long long sec : 6;
    unsigned long long msec : 13;  // setTime clamps it to 99
};

}  // namespace ui

#endif
