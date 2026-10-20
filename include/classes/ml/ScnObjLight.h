#ifndef CLASSES_ML_SCNOBJLIGHT_H
#define CLASSES_ML_SCNOBJLIGHT_H

#include "classes/ml/ScnObj.h"

namespace mm { class Mat44; }
namespace mm { class Vec3; }

namespace ml {
// table 0x7100B77D88
class ScnObjLight : public ::ml::ScnObj {
public:
    enum RENDER_INFO : int;
    virtual ~ScnObjLight();  // slot 0
    virtual void getName() const;  // slot 6
    virtual void isEnv() const;  // slot 8
    virtual void getFrame() const = 0;  // slot 9
    virtual void setFrame(float) = 0;  // slot 10
    virtual void getMaxFrame() const = 0;  // slot 11
    virtual void setFrameSpd(float) = 0;  // slot 12
    virtual void getFrameSpd() const = 0;  // slot 13
    virtual void setGroup(int) = 0;  // slot 14
    virtual void getGroup() const = 0;  // slot 15
    virtual void setOffsetPos(mm::Vec3 const&) = 0;  // slot 16
    virtual void getOffsetPos() const = 0;  // slot 17
    virtual void setPos(mm::Vec3 const&);  // slot 18
    virtual void setRot(mm::Vec3 const&);  // slot 19
    virtual void setScl(mm::Vec3 const&);  // slot 20
    virtual void setMat(mm::Mat44 const&);  // slot 21
    virtual void setDeugDisp2D(bool);  // slot 22
    virtual void setFromCaptureTool() = 0;  // slot 23
    virtual void setLocalIBLName(char const*) = 0;  // slot 24
};
}  // namespace ml

#endif
