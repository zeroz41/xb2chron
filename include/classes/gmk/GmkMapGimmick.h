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
        unsigned short m_effectId = 0;    // the row's "effectID" (only when GfGameManager::fn_71002A9E68())
        bool m_msgRay = false;            // flag "MSG_ray"
        TimeCond m_popTime;        // the row's "popTime"
        WeatherCond m_popWeather;  // the row's "popWeather"
        BootedGmkCond m_bootedGmk;  // the row's OP_gimmickType/ID
    };
    virtual ~GmkMapGimmick();  // slot 0
    void setSolved() const;
    bool isNotSolved() const;
    void validateEffectWithoutLodControl(int lodId, bool flag) const;
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
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x21);
    // 0x48: create stores (BdatInfo::m_nameRadius + 10) squared (the name is not the original's)
    float m_nameDistSq;
    // 0x50: the step update runs, cleared by dispose (the name is not the original's)
    void (GmkMapGimmick::*m_seq)(float);
    // 0x60: its game object, -1 for none (dispose destroys it; onGobEvent forgets it when it is destroyed; the name is
    // not the original's)
    gf::GF_OBJ_HANDLE* m_gob;
    unsigned char pad_68[0x8];
    // 0x70: its effects by LOD state (the destructor disposes them; Vector<GmkMapGimmick>::resize constructs it; the
    // name is not the original's)
    gf::GfFieldLodEffect m_lodEffect;
    // 0xA8, 0xA9: the enemy wave gimmick (TUnk_B6D418::fn_71005B3D64) sets the first and clears the second on the map
    // gimmick its row names (meaning unknown)
    bool pad_a8;
    bool pad_a9;
    unsigned char pad_aa[0x6];  // size from TGmkList::getInst's stride
};
}  // namespace gmk

#endif
