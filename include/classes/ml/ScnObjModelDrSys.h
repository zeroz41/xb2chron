#ifndef CLASSES_ML_SCNOBJMODELDRSYS_H
#define CLASSES_ML_SCNOBJMODELDRSYS_H

#include "classes/ml/ScnObjModel.h"
#include "classes/ml/DrMdlObj.h"

namespace ml { class Scn; }

namespace ml {
// table 0x7100B7EF28
class ScnObjModelDrSys : public ::ml::ScnObjModel {
public:
    ScnObjModelDrSys(ml::Scn* scn, const void* res, const char* name);
    // inline: ScnObjModelDrSysStandard's destructor inlines it (no table store of its own: empty body)
    virtual ~ScnObjModelDrSys() {}  // slot 0
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

    // 0x350 ScnObjModelDrSysStandard's constructor passes it to DrCreator::createMdl as the model's name (the name
    // and the size are not the original's)
    char m_mdlName[0x88];
    DrMdlObj* m_pMdlObj;  // 0x3D8 the name is not the original's
    unsigned char pad_3E0[0x8];
    const void* m_pRes;  // 0x3E8 the constructor's resource (the name is not the original's)
    unsigned char pad_3F0[0x44];
};
}  // namespace ml

#endif
