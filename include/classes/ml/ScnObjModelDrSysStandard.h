// not proven yet: its table differs from the original's (word 19: _ZN2ml24ScnObjModelDrSysStandard8setAlphaEf where the original has _ZN2ml16ScnObjModelDrSys8setAlphaEf)
#ifndef CLASSES_ML_SCNOBJMODELDRSYSSTANDARD_H
#define CLASSES_ML_SCNOBJMODELDRSYSSTANDARD_H

#include "classes/ml/ScnObjModel.h"

namespace ml {
// table 0x7100B7E828
class ScnObjModelDrSysStandard : public ::ml::ScnObjModel {
public:
    virtual ~ScnObjModelDrSysStandard();  // slot 0
    virtual void update();  // slot 2
    virtual void apply();  // slot 4
    virtual void tail();  // slot 5
    virtual void setAlpha(float);  // slot 17
    virtual void getAlpha() const;  // slot 18
    virtual void setWriteStencil(bool);  // slot 19
    virtual void setAlwaysTexStm(bool);  // slot 20
    virtual void isMdlTexStm() const;  // slot 21
    virtual void isMemTexStm() const;  // slot 22
    virtual void getAABBMax() const;  // slot 23
    virtual void getAABBMin() const;  // slot 24
    virtual void getCenter() const;  // slot 25
    virtual void getLength() const;  // slot 26
    virtual void setGroups(int);  // slot 27
    virtual void getGroups();  // slot 28
};
}  // namespace ml

#endif
