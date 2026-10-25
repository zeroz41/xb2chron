#ifndef CLASSES_ML_SCNOBJCLIPDYSYS_H
#define CLASSES_ML_SCNOBJCLIPDYSYS_H

#include "classes/ml/ScnObjClip.h"

namespace ml { class Scn; }

namespace ml {
// table 0x7100B7E638
class ScnObjClipDySys : public ::ml::ScnObjClip {
public:
    static ScnObjClipDySys* create(ml::Scn* scn, const void* res, int view);  // ScnRenderDrSys::create* forward to it
    virtual ~ScnObjClipDySys();  // slot 0
    virtual const char* getName() const;  // slot 6
};
}  // namespace ml

#endif
