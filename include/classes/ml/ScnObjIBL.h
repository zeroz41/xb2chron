#ifndef CLASSES_ML_SCNOBJIBL_H
#define CLASSES_ML_SCNOBJIBL_H

#include "classes/ml/ScnObj.h"

namespace ml { class WinProc; }

namespace ml {
// table 0x7100B78000
class ScnObjIBL : public ::ml::ScnObj {
public:
    virtual ~ScnObjIBL();  // slot 0
    virtual void vf8() = 0;  // slot 8
    virtual void vf9() = 0;  // slot 9
    virtual void vf10() = 0;  // slot 10
    virtual void dispDebugWindow(bool, char const*, ml::WinProc*);  // slot 11
    virtual void vf12() = 0;  // slot 12
};
}  // namespace ml

#endif
