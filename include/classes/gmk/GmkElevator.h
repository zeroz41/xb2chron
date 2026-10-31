#ifndef CLASSES_GMK_GMKELEVATOR_H
#define CLASSES_GMK_GMKELEVATOR_H

#include "classes/gmk/AGmkBase.h"
#include "classes/gmk/IGmkPhantomEventListener.h"
#include "plugin/Bdat.h"
#include "classes/gmk/GmkPhantom.h"
#include "classes/gmk/GmkCtrlVolSe.h"
#include "mm/mtl/FixedArray.h"

namespace gf { class GF_OBJ_HANDLE; }
#include "classes/gf/IGfObjListener.h"
namespace gmk { class GmkElevatorGobCustom; }

namespace gmk {
// a free function of this unit (GfFieldMapGimmick::seqLod_init calls it with a LOD id when its animation plays)
void applyLodFade(unsigned short lodId, bool flag);
// a base of gmk::GmkElevator no evidence names yet
class TUnk_B6CE88 {
public:
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&) = 0;
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&) = 0;
};
// table 0x7100B6CE10; base at 0x48 unknown (TUnk_B6CE88)
// 16-aligned: TGmkList::createGmk reserves its Vector with alignment 16 (the 16-aligned field is not typed yet)
class alignas(16) GmkElevator : public ::gmk::AGmkBase, public TUnk_B6CE88 {
public:
    // its size: the element size of its Vector<BdatInfo>::resize (0x7100617494); field names from the BDAT columns
    // create reads (the names are not the original's); the defaults are what Vector<BdatInfo>::resize constructs
    class BdatInfo {
    public:
        // user-provided: Vector<BdatInfo>::resize stores the defaults only (no zeroing of the pads first)
        BdatInfo() {}
        // fills it from the gimmick's BDAT row (0x71005AC88C)
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        unsigned short m_opCondition = 0;
        unsigned short m_callnameRadius = 10;
        unsigned short m_liftnameRadius = 5;
        unsigned short m_liftLod = 0;
        unsigned short m_shtALod = 0;
        unsigned short m_shtBLod = 0;
        unsigned short m_switchALod = 0;
        unsigned short m_switchBLod = 0;
        unsigned short m_switchSe = 0;
        unsigned short m_shutterSe = 0;
        unsigned short m_liftStartSe = 0;
        unsigned short m_liftLoopSe = 0;
        unsigned short m_liftStopSe = 0;
        unsigned char m_liftMinVolDist = 0;
        unsigned char m_liftMaxVolDist = 0;
        bool m_liftReverse = false;  // flag "lift_reverse"
        unsigned char pad_1d[0x3];
        float m_callLiftspeed = 2.0f;
        unsigned short m_missMsgId = 0;
        unsigned char pad_26[0x2];
        float m_elevatorNextwait = 0.0f;
        unsigned short m_liftAMapJumpId = 0;
        unsigned short m_liftBMapJumpId = 0;
    };
    // out of line (0x71005ACB14; Vector<GmkElevator>::resize calls it)
    GmkElevator();
    virtual ~GmkElevator();  // slot 0
    virtual gmk::GmkType getGmkType() const;  // slot 2
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4
    virtual void dispose();  // slot 5
    virtual void update(float);  // slot 6
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9
    virtual void onEnterPhantom(gmk::IGmkPhantomEventListener::OnEnterInfo const&);  // slot 11
    virtual void onLeavePhantom(gmk::IGmkPhantomEventListener::OnLeaveInfo const&);  // slot 12
    // which gimmick an item (one of m_gobs, by its index) acts on: 0 the elevator itself, 1..3 its locators (the
    // values are not named by any evidence)
    enum ItemType {};
    // the sound create plays (onPlayerAccessed passes 0; the values are not named by any evidence)
    enum SeType {};
    // what m_createInfo.m_data starts with (the name is not the original's)
    struct Data {
        unsigned short m_locatorId;  // GmkSet's GmkElevatorLocator list index of its first locator
        // one past its last locator: create wants three (the name is not the original's)
        unsigned short m_locatorEnd;
    };
    const AGmkBase* getGmkBaseByItemType(ItemType type) const;
    void createSe(SeType type, const mm::Vec3& pos);
    bool isCallSwitch(gf::GF_OBJ_HANDLE* gob) const;
    bool isLiftSwitch(gf::GF_OBJ_HANDLE* gob) const;
    // where the compass shows it (LocatorGimmick::update copies it into its position when it answers true)
    bool getPosForCompass(mm::Vec3& pos) const;
    // which of m_gobs it is (-1: none). Inline, no symbol: isCallSwitch (0 or 2) and isLiftSwitch (1 or 3) test
    // the first three/four entries in order with these answers (the name is not the original's)
    int getGobIndex(gf::GF_OBJ_HANDLE* gob) const {
        for (int i = 0; i < 4; i++) {
            if (m_gobs[i] == gob) {
                return i;
            }
        }
        return -1;
    }
    void clearGobInsts();
    void seqInit(float dt);
    void seqWaitToValidate_GfFieldLod(float dt);
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(42);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its address is in
    // GmkElevator's unit. What it does: walks PtrSingleton<GmkManager>'s gimmick vector (0xF358 buffer, 0xF360
    // count, "m_buffer != 0") and answers a flag over them; the gmk plugin's openPortal waits while it answers false.
    static bool fn_71005B928C();
    // 0x50..0x288: four phantoms, 0x2b0: four sound controls; the destructor destroys them in reverse
    // (the names are not the original's)
    // a FixedArray: the constructor calls FixedArray<GmkPhantom, 4>'s (out of line, 0x71005ACCD8)
    mm::mtl::FixedArray<GmkPhantom, 4> m_phantoms;
    // 0x290: its object instances (clearGobInsts destroys each, onGobEvent forgets a destroyed one; -1: none;
    // the name is not the original's)
    gf::GF_OBJ_HANDLE* m_gobs[4];
    mm::mtl::FixedArray<GmkCtrlVolSe, 4> m_ctrlVolSes;
    long pad_4b0;  // dispose sets it to -1 (meaning unknown)
    // the step update runs (symbols name them seqInit, seqUpIdle, ...; the name is not the original's)
    void (GmkElevator::*m_seq)(float dt);
    // set when the player accesses m_gobs[0], [2], [3], [1] (onPlayerAccessed); dispose clears them (the names
    // are not the original's)
    bool m_accessed0;
    bool m_accessed2;
    bool m_accessed3;
    bool m_accessed1;
    // the row's "elevator_nextwait" (create copies it; the name is not the original's); the constructor clears it
    // with the four flags (one 8-byte store); size from TGmkList::getInst's stride (0x4d0)
    float m_nextWait;  // the constructor clears it with the four flags (one 8-byte store); size from TGmkList::getInst's stride (0x4d0)
};
}  // namespace gmk

#endif
