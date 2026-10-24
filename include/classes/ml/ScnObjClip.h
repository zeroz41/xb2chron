#ifndef CLASSES_ML_SCNOBJCLIP_H
#define CLASSES_ML_SCNOBJCLIP_H

#include "classes/ml/ScnObj.h"
#include "mm/mtl/FixStr.h"

namespace ml {
// table 0x7100B77E60
class ScnObjClip : public ::ml::ScnObj {
public:
    ScnObjClip(Scn* scn);
    virtual ~ScnObjClip();  // slot 0
    virtual const char* getName() const;  // slot 6

    mm::mtl::FixStr<64> m_name;  // 0x14 "clipList" (the name is not the original's)
};
}  // namespace ml

#endif
