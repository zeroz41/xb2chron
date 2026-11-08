#ifndef CLASSES_GMK_TUNK_B6D6C8_H
#define CLASSES_GMK_TUNK_B6D6C8_H

#include "classes/gmk/AGmkBase.h"
#include "plugin/Bdat.h"
#include "mm/Vec3.h"

namespace gmk {
// 2.0.0's symbols name it and its gimmick object type GmkSealedStoneGob (TGmkList's 5th argument, which has no table or
// symbol of its own): the gimmick of kind 0x3F (GmkSet::createGmkLists' list slot 0x3F, bdat column "sealedStone"). Its
// table is 0x7100B6D6C8 (installed by its list's Vector<T0>::resize in each element).
class GmkSealedStoneGob;

class GmkSealedStone : public ::gmk::AGmkBase {
public:
    GmkSealedStone() {}  // inline, user-provided: the defaults are stored by Vector<T>::resize/extend, no zero fill
    // the overrides its table holds (slot functions still carry their placeholder symbols, given per slot)
    virtual ~GmkSealedStone();  // slot 0 (~GmkSealedStone)
    virtual gmk::GmkType getGmkType() const;  // slot 2 (getGmkType)
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4 (create)
    virtual void dispose();  // slot 5 (dispose)
    virtual void update(float);  // slot 6 (update)
    virtual void debugDraw() const;  // slot 7 (debugDraw)
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8 (onGobEvent)
    // its bdat row (0x40 bytes, 16-aligned: TGmkList::createGmk's Vector<BdatInfo> stride and alignment). The field
    // names come from the columns create reads (not the original's).
    class BdatInfo {
    public:
        // user-provided: Vector<BdatInfo>::resize stores the defaults only (no zeroing of the element first)
        BdatInfo() {}
        // out of line: initGmkBdatInfo calls it (symbol 0x71005B998C)
        void create(CBdatWrapper bdat, int row, const AGmkBase& gmk);
        const char* m_feedbackEffectName = nullptr;  // 0x0: "FeedbackEffectName"
        const char* m_finishEffectName = nullptr;    // 0x8: "FinishEffectName"
        float m_finishWaitTime = 0.0f;               // 0x10: "FinishWaitTime"
        unsigned char m_priority = 0;                // 0x14: "Priority" (when the table has it)
        float m_effectScale = 1.0f;                  // 0x18: "EffectScale"
        mm::Vec3 m_effectOffset = mm::Vec3::zero;    // 0x20: "EffectOffsetX/Y/Z"
        float m_visibleXZSq = 0.0f;                  // 0x30: "Visible_XZ" squared
        float m_visibleYSq = 0.0f;                   // 0x34: "Visible_Y" squared
        float m_invisibleXZSq = 0.0f;                // 0x38: "Invisible_XZ" (at least Visible_XZ + 1) squared
        float m_invisibleYSq = 0.0f;                 // 0x3C: "Invisible_Y" (at least Visible_Y + 1) squared
    };
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x3f);
    // 2.0.0's symbols name it. What it does: reads the game object handle at 0x48 (nothing when it is -1) and, branches
    // on the flag first (size 0x10C).
    void disposeGobInst(bool);
    // 2.0.0's symbols name them; update calls them (the row's Visible_XZ/Y and Invisible_XZ/Y distances)
    bool canPopGobInst() const;
    bool canDepopGobInst() const;
    // 2.0.0's symbols name it. What it does: destroys the old game object and creates a map-object one from the bound
    // bdat row (update calls it when canPopGobInst holds)
    void createGobInst();
    // 2.0.0's symbols name seqValidateResHandle, seqUpdate. What they do: create installs seqValidateResHandle, which
    // installs seqUpdate (an empty step).
    void seqValidateResHandle(float);
    void seqUpdate(float);
    // the game object (disposeGobInst does nothing when it is -1; the name is not the original's)
    gf::GF_OBJ_HANDLE* m_gob = reinterpret_cast<gf::GF_OBJ_HANDLE*>(-1);  // 0x48
    // 0x50/0x54: disposeGobInst(true) hands them to SCOM_DESTROY_GAME_OBJ::create and clears the time (the names are
    // not the original's; GmkMapObj's pair)
    float m_disposeWait = 0.0f;
    unsigned int m_disposeArg = 0;
    // 0x58: the step update runs while the gimmick is valid (create installs seqValidateResHandle; the name is not the
    // original's)
    void (GmkSealedStone::*m_seq)(float) = nullptr;
    float pad_68 = 0.0f;  // canPopGobInst needs it below 1, canDepopGobInst answers true from 1 on
    unsigned char pad_6c = 0;
    unsigned int m_effectHandle = 0;  // 0x70: dispose removes it from fw::EffectManager when non-zero (the name is not the original's)
    unsigned char pad_74 = 1;  // the data ends here: Vector<T>::expand's implicit copy copies up to it; the rest is alignment
};
}  // namespace gmk

#endif
