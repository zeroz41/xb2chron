#ifndef CLASSES_GMK_GMKJUMP_H
#define CLASSES_GMK_GMKJUMP_H

#include "classes/gmk/AGmkBase.h"
#include "mm/Vec3NA.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkJumpGobCustom; }

namespace gmk {
// table 0x7100B6CC40
class GmkJump : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize; the fields are not read yet
    class BdatInfo {
    public:
        unsigned char pad_0[0x2];
        // which message GfFieldJump::onFsSucceeded sends (0: MsgUnk_1000010, 1: MsgUnk_1000011, which also plays
        // fn_71005A7770's effect; the name is not the original's)
        unsigned char m_type;
        unsigned char pad_3[0x3];
    };
    // what AGmkBase::m_data points at for a jump gimmick (GfFieldJump::onFsSucceeded reads it; the struct and field
    // names are not the original's)
    struct alignas(8) Data {
        unsigned char pad_0[0x10];
        mm::Vec3NA m_pos;  // where the jump lands
        float m_param[3];  // passed on in MsgUnk_1000011 (meaning not known)
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_data); }
    const BdatInfo* getBdatInfo() const { return static_cast<const BdatInfo*>(m_bdatInfo); }
    virtual ~GmkJump();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*) {}  // slot 9
    virtual void debugUpdateMmf();  // slot 10
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it sits among GmkJump's
    // functions (GmkElevator.cpp's unit) and reads this gimmick's BdatInfo type byte. What it does: when
    // GfGameManager::fn_71002A9E68() answers true and the row's type is 1, tail-calls fn_71005A748C, which creates
    // the effect "ma40a_01_101_dlc" from GfFieldManager::getEffectPack(). GfFieldJump::onFsSucceeded calls it after
    // sending MsgUnk_1000011 (when fn_71002A9E68 answers true).
    void fn_71005A7770();
    static const gmk::GmkType TYPE = gmk::GmkType(37);
    unsigned char pad_48[0x38];  // fields: size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
