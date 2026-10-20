#ifndef CLASSES_ML_SCNPOOLOBJ_H
#define CLASSES_ML_SCNPOOLOBJ_H

#include "classes/ml/IScnRender.h"
#include "classes/ml/IWorkEvent.h"

namespace ml {
// table 0x7100B78078
class ScnPoolObj : public ::ml::IWorkEvent, public ::ml::IScnRender {
public:
    virtual ~ScnPoolObj();  // slot 0
};
}  // namespace ml

#endif
