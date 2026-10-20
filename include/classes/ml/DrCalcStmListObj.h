#ifndef CLASSES_ML_DRCALCSTMLISTOBJ_H
#define CLASSES_ML_DRCALCSTMLISTOBJ_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }

namespace ml {
// table 0x7100B7EDE8
class DrCalcStmListObj : public ::ml::IWorkEvent {
public:
    virtual ~DrCalcStmListObj();  // slot 0
    virtual void OnFileEvent(ml::EventFileTh*);  // slot 7
};
}  // namespace ml

#endif
