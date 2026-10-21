#ifndef CLASSES_ML_DRLIGHTOBJ_H
#define CLASSES_ML_DRLIGHTOBJ_H

namespace ml { class DrLightMan; }

namespace ml {
// table 0x7100B7B530
class DrLightObj {
public:
    virtual ~DrLightObj();  // slot 0
    virtual void update(ml::DrLightMan*) {}  // slot 2
};
}  // namespace ml

#endif
