// not proven yet: its table differs from the original's (word 29: =-440 where the original has =-448)
#ifndef CLASSES_ML_DEVFONTNX_H
#define CLASSES_ML_DEVFONTNX_H

#include "classes/ml/DevFont.h"

namespace ml {
// table 0x7100B77240
class DevFontNx : public ::ml::DevFont {
public:
    virtual ~DevFontNx();  // slot 0
    virtual void wkUpdate();  // slot 4
    virtual bool createFont();  // slot 6
    virtual void releaseFont();  // slot 7
};
}  // namespace ml

#endif
