#ifndef CLASSES_GMK_TUNK_B6D590_H
#define CLASSES_GMK_TUNK_B6D590_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"

namespace gmk {
// Placeholder name: the gimmick of kind 0x3C (GmkSet::createGmkLists' list slot 0x3C, bdat column "mapObj"),
// new in 3.0.1; nothing in 1.0.0 names it. Named by its table 0x7100B6D590 (the table its list's Vector<T0>::resize
// installs in each element).
//
// TUnk_B6D590Gob: placeholder name for its gimmick object type (TGmkList's 5th argument). No Gob class in the
// binary has a table or symbol of its own (they appear only inside TGmkList's mangled names), so it is named after
// the element's table, following the original's <element>Gob pattern (GmkTbox / GmkTboxGob).
class TUnk_B6D590Gob;

class TUnk_B6D590 : public ::gmk::AGmkBase {
public:
    // the overrides its table holds (slot functions still carry their placeholder symbols, given per slot)
    virtual ~TUnk_B6D590();  // slot 0 (fn_71005C3E44)
    virtual gmk::GmkType getGmkType() const;  // slot 2 (fn_71005C3F48)
    virtual bool isValid() const;  // slot 3 (fn_71005C3F50)
    virtual void dispose();  // slot 5 (fn_71005B7DAC)
    virtual void update(float);  // slot 6 (fn_71005B7E18)
    virtual void debugDraw() const;  // slot 7 (fn_71005B7E80)
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8 (fn_71005B8360)
    virtual void onPlayerAccessed(gf::GF_OBJ_HANDLE*);  // slot 9 (fn_71005C3F70)
    // its bdat row: empty (its Vector<BdatInfo>::resize stores nothing; createGmk's stride is 1)
    class BdatInfo {
    public:
        // inline and empty: initGmkBdatInfo (fn_71005D12B4) reads the table pointer (getBindedBdatFp) and stores
        // nothing, as GmkMob's
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk) {}
    };
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x3c);
    // the step update calls (the name is not the original's)
    void (TUnk_B6D590::*m_seq)(float dt);
    gf::GF_OBJ_HANDLE* m_gob;  // dispose destroys it unless it is -1 (the name is not the original's)
    bool m_isAccessed;  // onPlayerAccessed sets it, dispose clears it (the name is not the original's)
    unsigned char pad_61[0x3];
    // fields: size from the stride 0x78: Vector<TUnk_B6D590>::resize fn_71005D107C/fn_71005D15A4
    float m_waitTime;  // 0x64: fn_71005B7D44 stores its argument; fn_71005B7D5C waits until m_timer passes it (the name is not the original's)
    float m_timer;  // 0x68: the seq steps add dt to it (the name is not the original's)
    int m_bdatRow;  // 0x6c: the row of BDAT table 0x4D fn_71005B7BC4/fn_71005B7C2C read (the name is not the original's)
    int m_index;  // 0x70: those getters read column TresureResource<m_index + 1> / TresureSet<m_index + 1> (the name is not the original's)
    bool m_isDispOn;  // 0x74: fn_71005B801C shows the game object and activates its collision when set (the name is not the original's)
    unsigned char pad_75[0x3];

    // Placeholder names below: new in 3.0.1, nothing in 1.0.0's place names them. Members because their addresses sit
    // among this class's slots (dispose 0x71005B7DAC .. onGobEvent 0x71005B8360) and their callers pass a TUnk_B6D590.
    // What it does: the u16 column TresureResource<m_index + 1> of BDAT table 0x4D at row m_bdatRow (caller
    // gf::GfFieldTbox::start).
    unsigned int fn_71005B7BC4() const;
    // What it does: the u16 column TresureSet<m_index + 1> of BDAT table 0x4D at row m_bdatRow (caller
    // gf::GfFieldTbox::seqWaitOpenFieldTbox).
    unsigned int fn_71005B7C2C() const;
    // What it does: sets (true) or clears the low three bits of the game object's GfObjSetupGimmick flags (0x6c) and of
    // the GfObj's flags (0x110), as GmkSalvageLocator::setTargetable (caller gf::GfFieldTbox::seqCheckFs).
    void fn_71005B7C94(bool) const;
    // What it does: stores the wait time, clears m_timer and starts the step fn_71005B7D5C (caller
    // gf::TUnk_28E618::fn_710028E69C).
    void fn_71005B7D44(float);
    // What it does (step): adds dt to m_timer; past m_waitTime it pops the game object (fn_71005B810C) when there is
    // none and goes to fn_71005B8400.
    void fn_71005B7D5C(float);
    // What it does (caller gmk::fn_71005D3C54): applies m_isDispOn to the game object's display flag 8 and to its
    // GfComBehaviorGmk collision.
    void fn_71005B801C();
    // What it does: creates the game object (BDAT columns, setDisp, GfObjSetupGimmick); called by fn_71005B7D5C.
    void fn_71005B810C();
    // What it does (step): once onPlayerAccessed set m_isAccessed, clears m_timer and goes to fn_71005B841C.
    void fn_71005B8400(float);
    // What it does (step): adds dt to m_timer; past the float of BDAT table 0x7B's member 0 at row 0x52 it requests the
    // game object's destruction (SCOM_DESTROY_GAME_OBJ, 1.0) and ends the steps.
    void fn_71005B841C(float);
};
}  // namespace gmk

#endif
