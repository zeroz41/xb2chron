#ifndef CLASSES_ML_SCNOBJLIGHTDRSYS_H
#define CLASSES_ML_SCNOBJLIGHTDRSYS_H

#include "classes/ml/ScnObjLight.h"

namespace mm { class Vec3; }

namespace ml {
// table 0x7100B7E750
class ScnObjLightDrSys : public ::ml::ScnObjLight {
public:
    virtual ~ScnObjLightDrSys();  // slot 0
    virtual void apply();  // slot 4
    virtual void tail();  // slot 5
    virtual bool isEnv() const;  // slot 8
    virtual void getFrame() const;  // slot 9
    virtual void setFrame(float);  // slot 10
    virtual void getMaxFrame() const;  // slot 11
    virtual void setFrameSpd(float);  // slot 12
    virtual void getFrameSpd() const;  // slot 13
    virtual void setGroup(int);  // slot 14
    virtual void getGroup() const;  // slot 15
    virtual void setOffsetPos(mm::Vec3 const&);  // slot 16
    virtual void getOffsetPos() const;  // slot 17
    virtual void setDeugDisp2D(bool);  // slot 22
    virtual void setFromCaptureTool();  // slot 23
    virtual void setLocalIBLName(char const*);  // slot 24
};
}  // namespace ml

#endif
