#ifndef CLASSES_ML_SCNOBJCLIPDYSYS_H
#define CLASSES_ML_SCNOBJCLIPDYSYS_H

#include "classes/ml/ScnObjClip.h"
#include "mm/mtl/FixStr.h"

namespace ml { class Scn; }
namespace ml { class DrCalcClipObj; }

namespace ml {
// table 0x7100B7E638
class ScnObjClipDySys : public ::ml::ScnObjClip {
public:
    // inline: create's copy is the only one (no symbol of its own); defined in ScnObjClipDySys.cpp
    inline ScnObjClipDySys(ml::Scn* scn, const void* res, int view);
    static ScnObjClipDySys* create(ml::Scn* scn, const void* res, int view);  // ScnRenderDrSys::create* forward to it
    virtual ~ScnObjClipDySys();  // slot 0
    virtual const char* getName() const;  // slot 6

    DrCalcClipObj* m_pClipObj;  // 0x58, DrCreator::createClipObj's; the destructor releases it (the name is not the original's)
    int m_view;                 // 0x60, the view create was given (the name is not the original's)
    mm::mtl::FixStr<64> m_name;  // 0x64 "clipList": getName() (the name is not the original's)
};
}  // namespace ml

#endif
