#ifndef CLASSES_ML_DEVFONTLAYER_H
#define CLASSES_ML_DEVFONTLAYER_H

#include "classes/ml/WorkObj.h"

namespace ml {
// table 0x7100B75BA8
class DevFontLayer : public ::ml::WorkObj {
public:
    virtual ~DevFontLayer();  // slot 0
    virtual void wkUpdate();  // slot 9
    virtual void wkTail();  // slot 12
    virtual void wkStandbyLogout();  // slot 15
};
}  // namespace ml

#endif
