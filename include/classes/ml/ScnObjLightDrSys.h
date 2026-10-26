#ifndef CLASSES_ML_SCNOBJLIGHTDRSYS_H
#define CLASSES_ML_SCNOBJLIGHTDRSYS_H

#include "classes/ml/ScnObjLight.h"
#include "classes/ml/DrEnvironmentObj.h"


namespace ml { class Scn; }

namespace ml {
// table 0x7100B7E750
class ScnObjLightDrSys : public ::ml::ScnObjLight {
public:
    // inline: create's copy is the only one (no symbol of its own); defined in ScnObjLightDrSys.cpp
    inline ScnObjLightDrSys(ml::Scn* scn, const void* res, int view);
    static ScnObjLightDrSys* create(ml::Scn* scn, const void* res, int view);  // ScnRenderDrSys::create* forward to it
    virtual ~ScnObjLightDrSys();  // slot 0
    virtual void apply();  // slot 4
    virtual void tail();  // slot 5
    virtual bool isEnv() const;  // slot 8
    virtual float getFrame() const;  // slot 9
    virtual void setFrame(float);  // slot 10
    virtual float getMaxFrame() const;  // slot 11
    virtual void setFrameSpd(float);  // slot 12
    virtual float getFrameSpd() const;  // slot 13
    virtual void setGroup(int);  // slot 14
    virtual int getGroup() const;  // slot 15
    virtual void setOffsetPos(mm::Vec3 const&);  // slot 16
    virtual const mm::Vec3& getOffsetPos() const;  // slot 17
    virtual void setDeugDisp2D(bool);  // slot 22
    virtual void setFromCaptureTool();  // slot 23
    virtual void setLocalIBLName(char const*);  // slot 24

    const void* m_pRes;  // 0x318, the light resource create passes (the name is not the original's)
    DrEnvironmentObj* m_pEnvObj;  // 0x320, the getters forward to it (the name is not the original's)
    int m_view;  // 0x328, the view create passes (the name is not the original's)
};
}  // namespace ml

#endif
