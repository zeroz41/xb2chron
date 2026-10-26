#ifndef CLASSES_ML_SCNPOOLOBJ_H
#define CLASSES_ML_SCNPOOLOBJ_H

#include "classes/ml/IScnRender.h"
#include "classes/ml/IWorkEvent.h"

namespace ml { class ScnObj; }

namespace ml {
// table 0x7100B78078
class ScnPoolObj : public ::ml::IWorkEvent, public ::ml::IScnRender {
public:
    virtual ~ScnPoolObj();  // slot 0
    void release(ScnObj* item);
    // ScnObjModelDrSysStandard::create asks it for room for one before it makes a model (the parameter name is not
    // the original's)
    bool isValidInsert(unsigned short num) const;
    void insert(ScnObj* item);
};
}  // namespace ml

#endif
