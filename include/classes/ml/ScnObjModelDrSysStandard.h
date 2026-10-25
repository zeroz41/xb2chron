#ifndef CLASSES_ML_SCNOBJMODELDRSYSSTANDARD_H
#define CLASSES_ML_SCNOBJMODELDRSYSSTANDARD_H

#include "classes/ml/ScnObjModelDrSys.h"

namespace ml { class Scn; }

namespace ml {
// table 0x7100B7E828
class ScnObjModelDrSysStandard : public ::ml::ScnObjModelDrSys {
public:
    static ScnObjModelDrSysStandard* create(ml::Scn* scn, const void* res, const char* name, int view);  // ScnRenderDrSys::create* forward to it
    virtual ~ScnObjModelDrSysStandard();  // slot 0
    virtual void update();  // slot 2
    virtual void apply();  // slot 4
    virtual void tail();  // slot 5
};
}  // namespace ml

#endif
