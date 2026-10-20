// not proven yet: its table differs from the original's (word 8: _ZN2ml11TUnk_B75AA03vf6Ev where the original has __cxa_pure_virtual)
#ifndef CLASSES_ML_DEVFONT_H
#define CLASSES_ML_DEVFONT_H

#include "classes/ml/WorkObj.h"

namespace ml {
// a base of ml::DevFont no evidence names yet
class TUnk_B75AA0 {
public:
    virtual ~TUnk_B75AA0();
    virtual void wkStandbyLogin() = 0;
    virtual void wkStandbyLogout() = 0;
    virtual void wkUpdate() = 0;
    virtual void wkTail() = 0;
    virtual void vf6();
    virtual void vf7();
    unsigned char pad_8[0x8];  // fields: size from where the next base starts
};
// a base of ml::DevFont no evidence names yet
class TUnk_B75B88 {
public:
    virtual ~TUnk_B75B88();
};
// table 0x7100B75AA0; base at 0x0 unknown (TUnk_B75AA0), base at 0x1C0 unknown (TUnk_B75B88)
class DevFont : public TUnk_B75AA0, public ::ml::WorkObj, public TUnk_B75B88 {
public:
    virtual ~DevFont();  // slot 0
    virtual void wkStandbyLogin();  // slot 2
    virtual void wkStandbyLogout();  // slot 3
    virtual void wkUpdate();  // slot 4
    virtual void wkTail();  // slot 5
};
}  // namespace ml

#endif
