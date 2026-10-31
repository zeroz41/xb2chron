#ifndef CLASSES_GMK_GMKJUMP_H
#define CLASSES_GMK_GMKJUMP_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
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
        BdatInfo() {}  // user-provided: Vector<BdatInfo>::resize stores only the defaults (pads left)
        // inline: TGmkList::initGmkBdatInfo has no call of it
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {
            m_condition = (unsigned short)Bdat::getValCheck(bdat.m_fp, "Condition", row, 2);
            m_type = (unsigned char)Bdat::getValCheck(bdat.m_fp, "jumpType", row, 1);
            m_nameRadius = (unsigned short)Bdat::getValCheck(bdat.m_fp, "nameRadius", row, 2);
        }
        bool isPopCondMatched() const;
        unsigned short m_condition = 0;  // the row's "Condition" (a GfGameCond id; 0: none)
        // which message GfFieldJump::onFsSucceeded sends (0: MsgPcFieldNotifyWallJump, 1: MsgPcFieldNotifyBigJump, which also plays
        // fn_71005A7770's effect; the name is not the original's)
        unsigned char m_type = 0;  // the row's "jumpType"
        unsigned short m_nameRadius = 10;  // the row's "nameRadius"
    };
    // what AGmkBase::m_data points at for a jump gimmick (GfFieldJump::onFsSucceeded reads it; the struct and field
    // names are not the original's)
    struct alignas(8) Data {
        // where the jump gimmick stands: LocatorGimmick::update shows it on the compass (the name is not the original's)
        mm::Vec3NA m_startPos;
        unsigned char pad_c[0x4];
        mm::Vec3NA m_pos;  // where the jump lands
        float m_param[3];  // passed on in MsgPcFieldNotifyBigJump (meaning not known)
    };
    const Data* getData() const { return reinterpret_cast<const Data*>(m_createInfo.m_data); }
    const BdatInfo* getBdatInfo() const { return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo); }
    GmkJump() {}  // inline, user-provided: the defaults are stored by Vector<T>::resize/extend, no zero fill
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
    // sending MsgPcFieldNotifyBigJump (when fn_71002A9E68 answers true).
    void fn_71005A7770();
    // Placeholder name: new in 3.0.1. A member because its only caller, fn_71005A7770, passes this and it sits among
    // GmkJump's functions (between reqRecreateIcon and onGobEvent). What it does: creates the effect
    // "ma40a_01_101_dlc" from GfFieldManager::getEffectPack() (0x71005A748C).
    void fn_71005A748C();
    void createIcon();
    void reqRecreateIcon();
    // sets the flag reqRecreateIcon tests and removes the icon effect (fw::EffectManager::dead)
    void reqDeadIcon();
    static const gmk::GmkType TYPE = gmk::GmkType(37);
    void* pad_48 = nullptr;
    unsigned char pad_50 = 0;
    unsigned char pad_51[0x7];
    gf::GF_OBJ_HANDLE* m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);  // dispose destroys it (-1: none; the name is not the original's)
    void* pad_60 = nullptr;
    void* pad_68 = nullptr;
    unsigned int m_effectHandle;  // dispose removes it from fw::EffectManager (the name is not the original's)
    unsigned int pad_74 = 0;
    unsigned char pad_78 = 0;  // reqRecreateIcon clears it and makes the icon again when it was set
    unsigned char pad_79 = 1;  // the data ends here: Vector<T>::expand's implicit copy copies up to it; the rest is alignment
};
}  // namespace gmk

#endif
