#ifndef CLASSES_GMK_GMKJUMP_H
#define CLASSES_GMK_GMKJUMP_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "mm/Vec3NA.h"
#include "classes/gmk/DistHvCond.h"

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
        // onFsSucceeded's effect; the name is not the original's)
        unsigned char m_type = 0;  // the row's "jumpType"
        unsigned short m_nameRadius = 10;  // the row's "nameRadius"
    };
    // what AGmkBase::m_data points at for a jump gimmick (GfFieldJump::onFsSucceeded reads it; the struct and field
    // names are not the original's)
    struct Data {
        // where the jump gimmick stands: LocatorGimmick::update shows it on the compass; canPopGobInst passes it to
        // DistHvCond::isMatch as an mm::Vec3 (the name is not the original's)
        union {
            mm::Vec3 m_startPos;
            struct {
                float pad_0[3];
                // the icon's rotation about y (validateIconPos's for a jump of type 0; the name is not the original's)
                float m_rotY;
            };
        };
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
    // 2.0.0's symbols name it (new in 3.0.1). What it does: when
    // GfGameManager::isGameTypeIra() answers true and the row's type is 1, tail-calls suceededBigJump, which creates
    // the effect "ma40a_01_101_dlc" from GfFieldManager::getEffectPack(). GfFieldJump::onFsSucceeded calls it after
    // sending MsgPcFieldNotifyBigJump (when isGameTypeIra answers true).
    void onFsSucceeded() const;
    // 2.0.0's symbols name it (new in 3.0.1; between reqRecreateIcon and onGobEvent). What it does: creates the effect
    // "ma40a_01_101_dlc" from GfFieldManager::getEffectPack() (0x71005A748C).
    void suceededBigJump() const;
    // named by the symbols (update calls createGobInst when canPopGobInst answers true; createIcon tail-calls
    // validateIconPos)
    void createGobInst();
    void createIcon();
    void validateIconPos();
    void reqRecreateIcon();
    // sets the flag reqRecreateIcon tests and removes the icon effect (fw::EffectManager::dead)
    void reqDeadIcon();
    // 2.0.0's symbols name them; update calls them (pop: m_gob unset, pad_50 set, the interest position inside
    // ene_disp_r/h of the data's start position; depop: m_gob set and pad_50 clear or outside ene_release_r/h)
    bool canPopGobInst() const;
    bool canDepopGobInst() const;
    static const gmk::GmkType TYPE = gmk::GmkType(37);
    void* pad_48 = nullptr;
    unsigned char pad_50 = 0;
    unsigned char pad_51[0x7];
    gf::GF_OBJ_HANDLE* m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);  // dispose destroys it (-1: none; the name is not the original's)
    // squared distances from the current map's row of BDAT 0x5D (create): ene_disp_r/h, and with ene_release_r/h added
    DistHvCond m_eneDisp = {0.0f, 0.0f};
    DistHvCond m_eneRelease = {0.0f, 0.0f};
    unsigned int m_effectHandle;  // dispose removes it from fw::EffectManager (the name is not the original's)
    // create's squared distance from BDAT 0x7B member 1 (update shows the icon within it of the data's start
    // position, DistCond::isMatch; the name is not the original's)
    float m_iconDistSq = 0.0f;
    unsigned char pad_78 = 0;  // reqRecreateIcon clears it and makes the icon again when it was set
    // the icon effect's SendParam::m_flagB (validateIconPos); the data ends here: Vector<T>::expand's implicit copy
    // copies up to it; the rest is alignment
    unsigned char pad_79 = 1;
};
}  // namespace gmk

#endif
