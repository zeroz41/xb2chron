#ifndef CLASSES_ML_SCNOBJMODEL_H
#define CLASSES_ML_SCNOBJMODEL_H

#include "classes/ml/ScnObj.h"
#include "classes/ml/threadval.h"
#include "ml/AttrTransform.h"
#include "mm/mtl/FixStr.h"

namespace ml { class DebDraw; }
namespace ml { class WinProc; }
namespace mm { class Mat44; }
namespace mm { class Quat; }
namespace mm { class Vec3; }

namespace ml {
// table 0x7100B77F00
class ScnObjModel : public ::ml::ScnObj {
public:
    // what a model keeps per thread (0x140 bytes: threadval's tvSwap copies that much): its transform (getTrans
    // returns a bank's)
    struct RENDER_INFO {
        AttrTransform m_trans;  // (the name is not the original's)
    };
    // the offset its render applies, kept per thread (0x10 bytes)
    struct alignas(16) RENDER_OFFSET_INFO {
        unsigned char pad_0[0x10];
    };
    // the offset its render applies (fw::ModelObject::update copies its added offset there; the return type is
    // not in the symbol)
    mm::Vec3& getOffsetInfo(bool);
    void setFrameSpd(float spd);
    // the calculation thread's transform (true) or the render thread's (false)
    AttrTransform* getTrans(bool cpu);
    const AttrTransform* getTrans(bool cpu) const;
    void setClip(bool on);
    void setDisp(bool on);  // GfObjAcc::applyDisp passes whether the object and its parent show
    bool isDisp() const;
    bool isClip() const;
    virtual ~ScnObjModel();  // slot 0
    virtual void renderDebug(ml::DebDraw*);  // slot 3
    virtual void tail();  // slot 5
    virtual const char* getName() const;  // slot 6
    virtual void setDelete();  // slot 7
    virtual void setPos(mm::Vec3 const&);  // slot 8
    virtual void setPosWarp(mm::Vec3 const&);  // slot 9
    virtual void addPos(mm::Vec3 const&);  // slot 10
    virtual void setRot(mm::Vec3 const&);  // slot 11
    virtual void addRot(mm::Vec3 const&);  // slot 12
    virtual void addRot(mm::Quat const&);  // slot 13
    virtual void setScl(mm::Vec3 const&);  // slot 14
    virtual void addScl(mm::Vec3 const&);  // slot 15
    virtual void setMat(mm::Mat44 const&);  // slot 16
    virtual void setAlpha(float) = 0;  // slot 17
    virtual float getAlpha() const = 0;  // slot 18
    virtual void setWriteStencil(bool) = 0;  // slot 19
    virtual void setAlwaysTexStm(bool) = 0;  // slot 20
    virtual bool isMdlTexStm() const = 0;  // slot 21
    virtual bool isMemTexStm() const = 0;  // slot 22
    virtual const mm::Vec3& getAABBMax() const = 0;  // slot 23
    virtual const mm::Vec3& getAABBMin() const = 0;  // slot 24
    virtual const mm::Vec3& getCenter() const = 0;  // slot 25
    virtual float getLength() const = 0;  // slot 26
    virtual void setGroups(int) = 0;  // slot 27
    virtual int getGroups() = 0;  // slot 28
    virtual void dispDebugWindow(bool, char const*, ml::WinProc*) {}  // slot 29

    unsigned char pad_14[0xC];
    threadval<RENDER_INFO> m_info;  // its destructor's (the name is not the original's)
    threadval<RENDER_OFFSET_INFO> m_offsetInfo;  // getOffsetInfo returns one of its banks (the name is not the original's)
    mm::mtl::FixStr<32> m_name;  // 0x320 getName's, empty from the constructor (the name is not the original's)
    float m_frameSpd;             // setFrameSpd (the name is not the original's)
    unsigned char pad_348[0x4];
    unsigned int m_disp : 1;      // isDisp (the name is not the original's)
    unsigned int m_clip : 1;      // isClip; setClip sets it (the name is not the original's)
    unsigned int pad_bits2 : 2;
    unsigned int m_warp : 1;      // setPosWarp sets it (the name is not the original's)
    unsigned int pad_bits5 : 11;
    unsigned int m_dispReq : 1;   // setDisp sets it (the name is not the original's)
    unsigned int pad_bits17 : 15;  // unknown flags: isDisp loads the whole 32-bit unit
};
}  // namespace ml

#endif
