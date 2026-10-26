#ifndef CLASSES_ML_SCNOBJENVCOLIDR_H
#define CLASSES_ML_SCNOBJENVCOLIDR_H

#include "classes/ml/ScnObjEnvColi.h"

namespace ml { class Scn; }
namespace ml { class DrEnvColiObj; }

namespace ml {
// table 0x7100B7E688
class ScnObjEnvColiDr : public ::ml::ScnObjEnvColi {
public:
    // inline: create's copy is the only one (no symbol of its own); defined in ScnObjLightDrSys.cpp
    inline ScnObjEnvColiDr(ml::Scn* scn, const void* res, int view);
    static ScnObjEnvColiDr* create(ml::Scn* scn, const void* res, int view);  // ScnRenderDrSys::create* forward to it
    virtual ~ScnObjEnvColiDr();  // slot 0
    DrEnvColiObj* m_pColiObj;  // 0x58, DrCreator::createEnvColi's (the name is not the original's)
};
}  // namespace ml

#endif
