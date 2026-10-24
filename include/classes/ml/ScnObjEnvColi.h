#ifndef CLASSES_ML_SCNOBJENVCOLI_H
#define CLASSES_ML_SCNOBJENVCOLI_H

#include "classes/ml/ScnObj.h"
#include "mm/mtl/FixStr.h"

namespace ml {
// table 0x7100B77EB0
class ScnObjEnvColi : public ::ml::ScnObj {
public:
    ScnObjEnvColi(Scn* scn);
    virtual ~ScnObjEnvColi();  // slot 0
    virtual const char* getName() const;  // slot 6

    mm::mtl::FixStr<64> m_name;  // 0x14 "envColi" (the name is not the original's)
};
}  // namespace ml

#endif
