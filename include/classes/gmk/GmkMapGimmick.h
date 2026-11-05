#ifndef CLASSES_GMK_GMKMAPGIMMICK_H
#define CLASSES_GMK_GMKMAPGIMMICK_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/TimeCond.h"
#include "classes/gmk/WeatherCond.h"
#include "classes/gmk/BootedGmkCond.h"
#include "classes/gf/GfFieldLodColiAnim.h"
class CBdatWrapper;

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"

namespace gmk {
// table 0x7100B6CB08
class GmkMapGimmick : public ::gmk::AGmkBase {
public:
    // its size: the element size of its Vector<BdatInfo>::resize (0x7100632548 allocates count * 0x38; TGmkList<GmkMapGimmick>::~TGmkList (0x71005C74F4) frees the buffer with no destructor loop); the fields are not read yet
    class BdatInfo {
    public:
        // user-provided: Vector<BdatInfo>::resize stores the defaults only (no zeroing of the pads first)
        BdatInfo() {}
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        bool isPopCondMatched() const;
        unsigned short m_condition = 0;   // the row's "Condition" (a GfGameCond id; 0: none)
        unsigned short m_nameRadius = 5;  // the row's "nameRadius"
        unsigned short m_mapobjId = 0;    // the row's "mapobjID"
        unsigned short m_effectId = 0;    // the row's "effectID" (only when GfGameManager::isGameTypeIra())
        bool m_msgRay = false;            // flag "MSG_ray"
        TimeCond m_popTime;        // the row's "popTime"
        WeatherCond m_popWeather;  // the row's "popWeather"
        BootedGmkCond m_bootedGmk;  // the row's OP_gimmickType/ID
    };
    // user-provided: Vector<GmkMapGimmick>::resize/extend store the defaults below only (no zero fill of the element first)
    GmkMapGimmick() {}
    virtual ~GmkMapGimmick();  // slot 0
    void setSolved() const;
    bool isNotSolved() const;
    // creates the effect asset of the LOD model's row and, when it has one (with flag: only a looping one), starts it
    // on every seam part of the field's LOD model carrying the model's LOD id; false without an asset (or with a
    // gimmick set flagged off)
    bool validateEffectWithoutLodControl(int lodId, bool flag) const;
    const BdatInfo* getBdatInfo() const { return static_cast<const BdatInfo*>(m_createInfo.m_bdatInfo); }
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void debugDraw() const;  // slot 7
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    // its first step (create stores it; symbol name)
    void seqInit(float dt);
    // the step seqInit installs: pops/depops the game object, then tests the line of sight to it (symbol name)
    void seqUpdate(float dt);
    void createGobInst();
    bool canPopGobInst() const;
    bool canDepopGobInst() const;
    void validateLodState() const;
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x21);
    // 0x48: create stores (BdatInfo::m_nameRadius + 10) squared (the name is not the original's)
    float m_nameDistSq = 0.0f;
    // 0x50: the step update runs, cleared by dispose (the name is not the original's)
    void (GmkMapGimmick::*m_seq)(float) = nullptr;
    // 0x60: its game object, -1 for none (dispose destroys it; onGobEvent forgets it when it is destroyed; the name is
    // not the original's)
    gf::GF_OBJ_HANDLE* m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);
    unsigned char pad_68 = 1;
    // 0x70: its effects by LOD state (the destructor disposes them; Vector<GmkMapGimmick>::resize constructs it; the
    // name is not the original's)
    // mutable: the const validateEffectWithoutLodControl creates its asset and instances
    mutable gf::GfFieldLodEffect m_lodEffect;
    // 0xA8, 0xA9: the enemy wave gimmick (GmkEnemyWave::seqWaitToValidLinkGmkList) sets the first and clears the second on the map
    // gimmick its row names (meaning unknown)
    bool pad_a8 = false;
    bool pad_a9 = false;
    unsigned char pad_aa[0x6];  // size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
