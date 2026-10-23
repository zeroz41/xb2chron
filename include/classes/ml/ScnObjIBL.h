#ifndef CLASSES_ML_SCNOBJIBL_H
#define CLASSES_ML_SCNOBJIBL_H

#include "classes/ml/ScnObj.h"

namespace ml { class WinProc; }
namespace mm { class Vec3; }

namespace ml {
// table 0x7100B78000
class ScnObjIBL : public ::ml::ScnObj {
public:
    bool isDisp() const;
    virtual ~ScnObjIBL();  // slot 0
    virtual void setReferencePos(mm::Vec3 const&) = 0;  // slot 8
    virtual void getReferencePos() const = 0;  // slot 9
    virtual void setFromCaptureTool() = 0;  // slot 10
    virtual void dispDebugWindow(bool, char const*, ml::WinProc*) {}  // slot 11
    virtual void setName(char const*) = 0;  // slot 12

    unsigned int m_disp : 1;  // isDisp (the name is not the original's)
    unsigned int pad_bits : 31;  // unknown flags: isDisp loads the whole 32-bit unit
};
}  // namespace ml

#endif
