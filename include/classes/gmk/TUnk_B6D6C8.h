#ifndef CLASSES_GMK_TUNK_B6D6C8_H
#define CLASSES_GMK_TUNK_B6D6C8_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// Placeholder name: the gimmick of kind 0x3F (GmkSet::createGmkLists' list slot 0x3F, bdat column "sealedStone"),
// new in 3.0.1; nothing in 1.0.0 names it. Named by its table 0x7100B6D6C8 (the table its list's Vector<T0>::resize
// installs in each element).
//
// TUnk_B6D6C8Gob: placeholder name for its gimmick object type (TGmkList's 5th argument). No Gob class in the
// binary has a table or symbol of its own (they appear only inside TGmkList's mangled names), so it is named after
// the element's table, following the original's <element>Gob pattern (GmkTbox / GmkTboxGob).
class TUnk_B6D6C8Gob;

class TUnk_B6D6C8 : public ::gmk::AGmkBase {
public:
    // the overrides its table holds (slot functions still carry their placeholder symbols, given per slot)
    virtual ~TUnk_B6D6C8();  // slot 0 (fn_71005C4120)
    virtual gmk::GmkType getGmkType() const;  // slot 2 (fn_71005C41E8)
    virtual void create(gmk::AGmkBase::CreateInfo const&);  // slot 4 (fn_71005B9B7C)
    virtual void dispose();  // slot 5 (fn_71005B9BEC)
    virtual void update(float);  // slot 6 (fn_71005B9D44)
    virtual void debugDraw() const;  // slot 7 (fn_71005BA220)
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8 (fn_71005BA890)
    // its bdat row: complete because TGmkList's inline constructor needs Vector<BdatInfo>; the size is not read
    // yet (placeholder: no fields declared)
    class BdatInfo {};
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x3f);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because its dispose (fn_71005B9BEC)
    // calls it with `this` (and 0). What it does: reads the game object handle at 0x48 (nothing when it is -1) and,
    // branches on the flag first (size 0x10C).
    void fn_71005B9C38(bool);
    // Placeholder names: new in 3.0.1, nothing in 1.0.0's place names them. Members because they are the steps m_seq
    // holds (update calls m_seq with its dt). What they do: create installs fn_71005B9BDC, which installs fn_71005BA88C
    // (an empty step).
    void fn_71005B9BDC(float);
    void fn_71005BA88C(float);
    unsigned char pad_48[0x10];  // fields: size from the stride 0x78: Vector<TUnk_B6D6C8>::resize fn_7100637D9C
    // 0x58: the step update runs while the gimmick is valid (create installs fn_71005B9BDC; the name is not the
    // original's)
    void (TUnk_B6D6C8::*m_seq)(float);
    unsigned char pad_68[0x8];
    unsigned int m_effectHandle;  // 0x70: dispose removes it from fw::EffectManager when non-zero (the name is not the original's)
    unsigned char pad_74[0x4];
};
}  // namespace gmk

#endif
