#ifndef CLASSES_GMK_TUNK_B6D6C8_H
#define CLASSES_GMK_TUNK_B6D6C8_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// 2.0.0's symbols name it and its gimmick object type GmkSealedStoneGob (TGmkList's 5th argument, which has no table or
// symbol of its own): the gimmick of kind 0x3F (GmkSet::createGmkLists' list slot 0x3F, bdat column "sealedStone"). Its
// table is 0x7100B6D6C8 (installed by its list's Vector<T0>::resize in each element).
class GmkSealedStoneGob;

class GmkSealedStone : public ::gmk::AGmkBase {
public:
    // the overrides its table holds (slot functions still carry their placeholder symbols, given per slot)
    virtual ~GmkSealedStone();  // slot 0 (~GmkSealedStone)
    virtual gmk::GmkType getGmkType() const;  // slot 2 (getGmkType)
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4 (create)
    virtual void dispose();  // slot 5 (dispose)
    virtual void update(float);  // slot 6 (update)
    virtual void debugDraw() const;  // slot 7 (debugDraw)
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8 (onGobEvent)
    // its bdat row: complete because TGmkList's inline constructor needs Vector<BdatInfo>; the size is not read
    // yet (placeholder: no fields declared)
    class BdatInfo {};
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x3f);
    // 2.0.0's symbols name it. What it does: reads the game object handle at 0x48 (nothing when it is -1) and, branches
    // on the flag first (size 0x10C).
    void disposeGobInst(bool);
    // 2.0.0's symbols name seqValidateResHandle, seqUpdate; the fn_ names are placeholders. What they do: create
    // installs seqValidateResHandle, which installs seqUpdate (an empty step).
    void seqValidateResHandle(float);
    void seqUpdate(float);
    unsigned char pad_48[0x10];  // fields: size from the stride 0x78: Vector<GmkSealedStone>::resize resize
    // 0x58: the step update runs while the gimmick is valid (create installs seqValidateResHandle; the name is not the
    // original's)
    void (GmkSealedStone::*m_seq)(float);
    unsigned char pad_68[0x8];
    unsigned int m_effectHandle;  // 0x70: dispose removes it from fw::EffectManager when non-zero (the name is not the original's)
    unsigned char pad_74[0x4];
};
}  // namespace gmk

#endif
