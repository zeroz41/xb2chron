#ifndef CLASSES_ML_SCNOBJCLIP_H
#define CLASSES_ML_SCNOBJCLIP_H

#include "classes/ml/ScnObj.h"

namespace ml {
// table 0x7100B77E60
class ScnObjClip : public ::ml::ScnObj {
public:
    virtual ~ScnObjClip();  // slot 0
    virtual void getName() const;  // slot 6
};
}  // namespace ml

#endif
