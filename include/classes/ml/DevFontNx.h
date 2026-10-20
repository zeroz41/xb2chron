// not proven yet: its table differs from the original's (word 8: _ZN2ml11TUnk_B75AA03vf6Ev where the original has _ZN2ml9DevFontNx10createFontEv)
#ifndef CLASSES_ML_DEVFONTNX_H
#define CLASSES_ML_DEVFONTNX_H

#include "classes/ml/DevFont.h"

namespace ml {
// table 0x7100B77240
class DevFontNx : public ::ml::DevFont {
public:
    virtual ~DevFontNx();  // slot 0
    virtual void wkUpdate();  // slot 4
    virtual void createFont();  // slot 6
    virtual void releaseFont();  // slot 7
};
}  // namespace ml

#endif
