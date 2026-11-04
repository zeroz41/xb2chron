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
    // the overrides its table holds (slot functions still carry their placeholder symbols, given per slot)
    virtual ~GmkBattleChallengePortal();  // slot 0 (fn_71005C3F7C)
    virtual gmk::GmkType getGmkType() const;  // slot 2 (fn_71005C3FF4)
    virtual bool isValid() const;  // slot 3 (fn_71005C3FFC)
    virtual void dispose();  // slot 5 (fn_71005B87E0)
    virtual void update(float);  // slot 6 (fn_71005B896C)
    virtual void debugDraw() const;  // slot 7 (fn_71005B89E8)
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8 (fn_71005B91A0)
    // its bdat row (TGmkList's inline constructor needs Vector<BdatInfo>). The fields are the ones
    // fn_71005B869C, fn_71005B8E18 and fn_71005B8FA0 read, laid out as GmkNpc::BdatInfo's after its Group and
    // BattleReaction; the size is not read yet and the names are not the original's
    class BdatInfo {
    public:
        // its row reader: out of line (fn_71005B84D0), called by initGmkBdatInfo (fn_71005D3388) where the template
        // calls T1::create (so the name is the template's; the CBdatWrapper parameter as GmkElevator::BdatInfo's)
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        // Placeholder name (new in 3.0.1): its row's pop conditions (scenario flag range, quest state range, time
        // range, game condition), as GmkEvent::BdatInfo::isCondMatched plus the time range
        bool fn_71005B869C() const;
        unsigned short m_condition;      // 0x0
        ScenarioFlagCond m_scenarioFlag; // 0x2
        QuestFlagCond m_questFlag;       // 0x6
        TimeCond m_timeRange;            // 0x10
        float m_visibleXZSq;             // 0x20: compared with the interest position's squared XZ distance
        float m_visibleYSq;              // 0x24: likewise its squared Y distance
        float m_invisibleXZSq;           // 0x28: fn_71005B8FA0's XZ limit
        float m_invisibleYSq;            // 0x2C: fn_71005B8FA0's Y limit
    };
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x3d);
    // the step update calls while the gimmick is valid (the name is not the original's)
    void (GmkBattleChallengePortal::*m_seq)(float dt);
    // fields: size from the stride 0x80: Vector<GmkBattleChallengePortal>::resize fn_71005D3180
    void* m_portalEffect0;  // 0x58: seqValidateResHandle searches "ex_portal_01" in the field's effect pack (the name is not the original's)
    void* m_portalEffect1;  // 0x60: the same for "ex_portal_02" (the name is not the original's)
    unsigned int m_effectHandle0;  // 0x68: disposeGobInst kills or fades it out (the name is not the original's)
    unsigned int m_effectHandle1;  // 0x6c: likewise (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_gob;  // 0x70: dispose destroys it unless it is -1 (the name is not the original's)
    float m_timer;  // 0x78: fn_71005B90D8 sets it from BDAT table 0x7B's member 0 at row 0x55; seqWait counts it down (the name is not the original's)
    unsigned char pad_7c[0x4];

    // 2.0.0's symbols name them. What it does (step; Vector<GmkBattleChallengePortal>::resize installs it): finds the
    // two portal effects in gf::GfFieldManager's effect pack, then goes to seqUpdate.
    void seqValidateResHandle(float);
    // What it does: destroys the game object (true: requests SCOM_DESTROY_GAME_OBJ, false: destroys it now) and
    // fades out (true) or kills (false) both effect handles; dispose and onGobEvent do its false case.
    void disposeGobInst(bool);
    // What it does (called by seqUpdate): pops the game object (fn_71005B8D1C) and plays its effects.
    void createGobInst();
    // What it does: creates the game object and its effects (true from fn_71005B90D8).
    void fn_71005B8D1C(bool);
    // What it does: true when the gimmick should pop its game object (BdatInfo conditions, distance to the
    // interest point).
    bool fn_71005B8E18();
    // What it does: true when the game object should go (its BdatInfo conditions fail or the interest point is
    // outside the invisible range).
    bool fn_71005B8FA0();
    // 2.0.0's symbols name it.
    bool isPopCondMatchedExceptDist() const;
    // What it does (step): pops (createGobInst) when fn_71005B8E18 says so, else depops (disposeGobInst(true)) when
    // fn_71005B8FA0 says so.
    void seqUpdate(float);
    // What it does (step; GmkElevator::fn_71005B928C installs it): pops the game object (fn_71005B8D1C(true)), plays
    // the map's portal sound (map 0x3A: 2, 9: 0x10, 3: 0xD, else 0) and waits m_timer in seqWait.
    void fn_71005B90D8(float);
    // What it does (step): nothing (the end step seqWait and GmkElevator::fn_71005B928C install).
    void seqFinish(float);
    // What it does (step): counts m_timer down by dt, then goes to seqFinish.
    void seqWait(float);
};
}  // namespace gmk

#endif
