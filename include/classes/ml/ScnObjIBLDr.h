#ifndef CLASSES_ML_SCNOBJIBLDR_H
#define CLASSES_ML_SCNOBJIBLDR_H

#include "classes/ml/ScnObjIBL.h"

namespace ml { class WinProc; }
namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7E6D8
class ScnObjIBLDr : public ::ml::ScnObjIBL {
public:
    virtual ~ScnObjIBLDr();  // slot 0
    virtual void apply();  // slot 4
    virtual const char* getName() const;  // slot 6
    virtual void setReferencePos(mm::Vec3 const&);  // slot 8
    virtual void getReferencePos() const;  // slot 9
    virtual void setFromCaptureTool();  // slot 10
    virtual void dispDebugWindow(bool, char const*, ml::WinProc*);  // slot 11
    virtual void setName(char const*);  // slot 12
};
}  // namespace ml

#endif
