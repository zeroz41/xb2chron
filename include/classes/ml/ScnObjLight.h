#ifndef CLASSES_ML_SCNOBJLIGHT_H
#define CLASSES_ML_SCNOBJLIGHT_H

#include "classes/ml/ScnObj.h"
#include "classes/ml/threadval.h"
#include "ml/AttrTransform.h"
#include "mm/mtl/FixStr.h"

namespace mm { class Mat44; }
namespace mm { class Vec3; }

namespace ml {
// table 0x7100B77D88
class ScnObjLight : public ::ml::ScnObj {
public:
    // what a light keeps per thread (0x140 bytes: threadval's tvSwap copies that much): its transform (getTrans
    // returns a bank's)
    struct RENDER_INFO {
        AttrTransform m_trans;  // (the name is not the original's)
    };
    // the calculation thread's transform (true) or the render thread's (false)
    AttrTransform* getTrans(bool cpu);
    bool isDisp() const;
    bool isOfsMatrix() const;
    explicit ScnObjLight(Scn* scn);
    // inline: ScnObjLightDrSys's destructors inline it (Scn.cpp's copy is the one its table emits)
    virtual ~ScnObjLight() {}  // slot 0
    virtual const char* getName() const;  // slot 6
    virtual bool isEnv() const { return false; }  // slot 8
    virtual float getFrame() const = 0;  // slot 9
    virtual void setFrame(float) = 0;  // slot 10
    virtual float getMaxFrame() const = 0;  // slot 11
    virtual void setFrameSpd(float) = 0;  // slot 12
    virtual float getFrameSpd() const = 0;  // slot 13
    virtual void setGroup(int) = 0;  // slot 14
    virtual int getGroup() const = 0;  // slot 15
    virtual void setOffsetPos(mm::Vec3 const&) = 0;  // slot 16
    virtual const mm::Vec3& getOffsetPos() const = 0;  // slot 17
    virtual void setPos(mm::Vec3 const&);  // slot 18
    virtual void setRot(mm::Vec3 const&);  // slot 19
    virtual void setScl(mm::Vec3 const&);  // slot 20
    virtual void setMat(mm::Mat44 const&);  // slot 21
    virtual void setDeugDisp2D(bool) {}  // slot 22
    virtual void setFromCaptureTool() = 0;  // slot 23
    virtual void setLocalIBLName(char const*) = 0;  // slot 24

    mm::mtl::FixStr<64> m_name;  // 0x14 empty from the constructor (the name is not the original's)
    unsigned char pad_58[0x8];
    threadval<RENDER_INFO> m_info;  // its destructor's (the name is not the original's)
    unsigned int m_disp : 1;       // isDisp (the name is not the original's)
    unsigned int m_ofsMatrix : 1;  // isOfsMatrix (the name is not the original's)
    unsigned int pad_bits : 30;  // unknown flags: isDisp loads the whole 32-bit unit
};
}  // namespace ml

#endif
