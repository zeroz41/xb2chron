#ifndef CLASSES_ML_DRCALCSTMLISTOBJ_H
#define CLASSES_ML_DRCALCSTMLISTOBJ_H

#include "classes/ml/IWorkEvent.h"

namespace ml { class EventFileTh; }

namespace ml {
// table 0x7100B7EDE8
class DrCalcStmListObj : public ::ml::IWorkEvent {
public:
    virtual ~DrCalcStmListObj();  // slot 0
    virtual bool OnFileEvent(ml::EventFileTh*);  // slot 7

    // the values (0..2) DrStmReadCheck::update passes have no recovered names
    enum DrTexUseMode {};

    void release();
    void setUseMode(DrTexUseMode mode);
    // the pointer at 0x18 of the object at 0x48 once the flag at 0x82 is set, else null (the return type is not
    // known)
    void* getAdder();
};
}  // namespace ml

#endif
