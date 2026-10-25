#ifndef CLASSES_ML_SCNOBJENVCOLIDR_H
#define CLASSES_ML_SCNOBJENVCOLIDR_H

#include "classes/ml/ScnObjEnvColi.h"

namespace ml { class Scn; }

namespace ml {
// table 0x7100B7E688
class ScnObjEnvColiDr : public ::ml::ScnObjEnvColi {
public:
    static ScnObjEnvColiDr* create(ml::Scn* scn, const void* res, int view);  // ScnRenderDrSys::create* forward to it
    virtual ~ScnObjEnvColiDr();  // slot 0
};
}  // namespace ml

#endif
