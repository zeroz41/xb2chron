#ifndef CLASSES_ML_SCNOBJCLIPDYSYS_H
#define CLASSES_ML_SCNOBJCLIPDYSYS_H

#include "classes/ml/ScnObj.h"

namespace ml {
// table 0x7100B7E638
class ScnObjClipDySys : public ::ml::ScnObj {
public:
    virtual ~ScnObjClipDySys();  // slot 0
    virtual void getName() const;  // slot 6
};
}  // namespace ml

#endif
