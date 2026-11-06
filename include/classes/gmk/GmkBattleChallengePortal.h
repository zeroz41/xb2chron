#ifndef CLASSES_GMK_TUNK_B6D5F8_H
#define CLASSES_GMK_TUNK_B6D5F8_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "classes/gmk/ScenarioFlagCond.h"
#include "classes/gmk/QuestFlagCond.h"
#include "classes/gmk/TimeCond.h"

namespace gmk {
// 2.0.0's symbols name it and its gimmick object type GmkBattleChallengePortalGob (TGmkList's 5th argument, which has
// no table or symbol of its own): the gimmick of kind 0x3D (GmkSet::createGmkLists' list slot 0x3D, bdat column "npc").
// Its table is 0x7100B6D5F8 (installed by its list's Vector<T0>::resize in each element).
class GmkBattleChallengePortalGob;

class GmkBattleChallengePortal : public ::gmk::AGmkBase {
public:
    GmkBattleChallengePortal() {}  // inline, user-provided: the defaults are stored by Vector<T>::resize/extend, no zero fill
    // the overrides its table holds
    virtual ~GmkBattleChallengePortal();  // slot 0 (~GmkBattleChallengePortal)
    virtual gmk::GmkType getGmkType() const;  // slot 2 (getGmkType)
    virtual bool isValid() const;  // slot 3 (isValid)
    virtual void dispose();  // slot 5 (dispose)
    virtual void update(float);  // slot 6 (update)
    virtual void debugDraw() const;  // slot 7 (debugDraw)
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8 (onGobEvent)
    // its bdat row (TGmkList's inline constructor needs Vector<BdatInfo>). The fields are the ones
    // isPopCommonCondMatched, canPopGobInst and canDepopGobInst read, laid out as GmkNpc::BdatInfo's after its Group and
    // BattleReaction; the size is not read yet and the names are not the original's
    class BdatInfo {
    public:
        // its row reader: out of line (create), called by initGmkBdatInfo (initGmkBdatInfo) where the template
        // calls T1::create (so the name is the template's; the CBdatWrapper parameter as GmkElevator::BdatInfo's)
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        // user-provided: Vector<BdatInfo>::resize stores the defaults only (no zeroing of the element first)
        BdatInfo() {}
        // 2.0.0's symbols name it: its row's pop conditions (scenario flag range, quest state range, time
        // range, game condition), as GmkEvent::BdatInfo::isCondMatched plus the time range
        bool isPopCommonCondMatched(const AGmkBase& gmk) const;
        unsigned short m_condition;      // 0x0: not set by Vector<BdatInfo>::resize
        ScenarioFlagCond m_scenarioFlag; // 0x2
        QuestFlagCond m_questFlag;       // 0x6
        TimeCond m_timeRange;            // 0x10
        float m_visibleXZSq = 0.0f;             // 0x20: compared with the interest position's squared XZ distance
        float m_visibleYSq = 0.0f;              // 0x24: likewise its squared Y distance
        float m_invisibleXZSq = 0.0f;           // 0x28: canDepopGobInst's XZ limit
        float m_invisibleYSq = 0.0f;            // 0x2C: canDepopGobInst's Y limit
    };
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x3d);
    // 2.0.0's symbols name it (its address is in GmkElevator's unit). What it does: walks PtrSingleton<GmkManager>'s
    // gimmick vector (0xF358 buffer, 0xF360 count, "m_buffer != 0") and answers a flag over them; the gmk plugin's
    // openPortal (gmk.openPortal) waits while it answers false. It installs seqOpen and seqFinish.
    static bool openPortal();
    // the step update calls while the gimmick is valid (the name is not the original's)
    void (GmkBattleChallengePortal::*m_seq)(float dt) = &GmkBattleChallengePortal::seqValidateResHandle;
    // fields: size from the stride 0x80: Vector<GmkBattleChallengePortal>::resize resize
    // 0x58: seqValidateResHandle searches "ex_portal_01" and "ex_portal_02" in the field's effect pack; createEffect
    // indexes it (the name is not the original's)
    void* m_portalEffect[2] = {nullptr, nullptr};
    // 0x68: the effects createEffect creates from m_portalEffect, by the same index; disposeGobInst kills or fades
    // them out (the name is not the original's)
    unsigned int m_effectHandle[2] = {0, 0};
    gf::GF_OBJ_HANDLE* m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);  // 0x70: dispose destroys it unless it is -1 (the name is not the original's)
    float m_timer = 0.0f;  // 0x78: seqOpen sets it from BDAT table 0x7B's member 0 at row 0x55; seqWait counts it down (the name is not the original's)
    // the data ends here: Vector<T>::expand's implicit copy copies up to it; the rest is alignment

    // 2.0.0's symbols name them. What it does (step; Vector<GmkBattleChallengePortal>::resize installs it): finds the
    // two portal effects in gf::GfFieldManager's effect pack, then goes to seqUpdate.
    void seqValidateResHandle(float);
    // What it does: destroys the game object (true: requests SCOM_DESTROY_GAME_OBJ, false: destroys it now) and
    // fades out (true) or kills (false) both effect handles; dispose and onGobEvent do its false case.
    void disposeGobInst(bool);
    // What it does (called by seqUpdate): pops the game object (createEffect) and plays its effects.
    void createGobInst();
    // What it does: creates the index-th portal effect (0 from createGobInst, 1 from seqOpen) at the gimmick's
    // matrix; false when the effect manager made none.
    bool createEffect(unsigned int index);
    // What it does: true when the gimmick should pop its game object (BdatInfo conditions, distance to the
    // interest point).
    bool canPopGobInst() const;
    // What it does: true when the game object should go (its BdatInfo conditions fail or the interest point is
    // outside the invisible range).
    bool canDepopGobInst() const;
    // 2.0.0's symbols name it.
    bool isPopCondMatchedExceptDist() const;
    // What it does (step): pops (createGobInst) when canPopGobInst says so, else depops (disposeGobInst(true)) when
    // canDepopGobInst says so.
    void seqUpdate(float);
    // What it does (step; openPortal installs it): pops the game object (createEffect(true)), plays
    // the map's portal sound (map 0x3A: 2, 9: 0x10, 3: 0xD, else 0) and waits m_timer in seqWait.
    void seqOpen(float);
    // What it does (step): nothing (the end step seqWait and openPortal install).
    void seqFinish(float);
    // What it does (step): counts m_timer down by dt, then goes to seqFinish.
    void seqWait(float);
};
}  // namespace gmk

#endif
