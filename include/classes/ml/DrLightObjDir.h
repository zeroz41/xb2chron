#ifndef CLASSES_ML_DRLIGHTOBJDIR_H
#define CLASSES_ML_DRLIGHTOBJDIR_H

namespace ml { class DrLightMan; }

namespace ml {
// table 0x7100B7B580
class DrLightObjDir {
public:
    virtual ~DrLightObjDir();  // slot 0
    virtual void update(ml::DrLightMan*);  // slot 2
};
}  // namespace ml

#endif
