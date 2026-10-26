#ifndef CLASSES_ML_DRLIGHTOBJDIR_H
#define CLASSES_ML_DRLIGHTOBJDIR_H

#include "classes/ml/DrLightObj.h"

namespace ml { class DrLightMan; }

namespace ml {
// table 0x7100B7B580
class DrLightObjDir : public ::ml::DrLightObj {
public:
    virtual ~DrLightObjDir();  // slot 0
    virtual void update(ml::DrLightMan*);  // slot 2

    // 1.0.0 has both out of line; 3.0.1 only inlines them into the destructor
    void releaseDir();
    void deleteDirShadow();
};
}  // namespace ml

#endif
