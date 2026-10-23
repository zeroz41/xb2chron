#ifndef CLASSES_ML_SCNOBJMODELDRSYS_H
#define CLASSES_ML_SCNOBJMODELDRSYS_H

#include "classes/ml/ScnObjModel.h"
#include "classes/ml/DrMdlObj.h"

namespace ml {
// table 0x7100B7EF28
class ScnObjModelDrSys : public ::ml::ScnObjModel {
public:
    virtual ~ScnObjModelDrSys();  // slot 0
    virtual void update();  // slot 2
    virtual void apply();  // slot 4
    virtual void setAlpha(float);  // slot 17
    virtual float getAlpha() const;  // slot 18
    virtual void setWriteStencil(bool);  // slot 19
    virtual void setAlwaysTexStm(bool);  // slot 20
    virtual bool isMdlTexStm() const;  // slot 21
    virtual bool isMemTexStm() const;  // slot 22
    virtual const mm::Vec3& getAABBMax() const;  // slot 23
    virtual const mm::Vec3& getAABBMin() const;  // slot 24
    virtual const mm::Vec3& getCenter() const;  // slot 25
    virtual float getLength() const;  // slot 26
    virtual void setGroups(int);  // slot 27
    virtual int getGroups();  // slot 28

    // ScnObjModel's own fields are not declared yet: pad_8 covers them and this class's up to 0x3D8
    unsigned char pad_8[0x3D0];
    DrMdlObj* m_pMdlObj;  // the name is not the original's
};
}  // namespace ml

#endif
