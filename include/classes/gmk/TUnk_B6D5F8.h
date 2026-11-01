#ifndef CLASSES_GMK_TUNK_B6D5F8_H
#define CLASSES_GMK_TUNK_B6D5F8_H

#include "classes/gmk/AGmkBase.h"

namespace gmk {
// Placeholder name: the gimmick of kind 0x3D (GmkSet::createGmkLists' list slot 0x3D, bdat column "npc"),
// new in 3.0.1; nothing in 1.0.0 names it. Named by its table 0x7100B6D5F8 (the table its list's Vector<T0>::resize
// installs in each element).
//
// TUnk_B6D5F8Gob: placeholder name for its gimmick object type (TGmkList's 5th argument). No Gob class in the
// binary has a table or symbol of its own (they appear only inside TGmkList's mangled names), so it is named after
// the element's table, following the original's <element>Gob pattern (GmkTbox / GmkTboxGob).
class TUnk_B6D5F8Gob;

class TUnk_B6D5F8 : public ::gmk::AGmkBase {
public:
    // the overrides its table holds (slot functions still carry their placeholder symbols, given per slot)
    virtual ~TUnk_B6D5F8();  // slot 0 (fn_71005C3F7C)
    virtual gmk::GmkType getGmkType() const;  // slot 2 (fn_71005C3FF4)
    virtual bool isValid() const;  // slot 3 (fn_71005C3FFC)
    virtual void dispose();  // slot 5 (fn_71005B87E0)
    virtual void update(float);  // slot 6 (fn_71005B896C)
    virtual void debugDraw() const;  // slot 7 (fn_71005B89E8)
    virtual void onGobEvent(gf::IGfObjListener::OBJEVT, gf::GF_OBJ_HANDLE*);  // slot 8 (fn_71005B91A0)
    // its bdat row: complete because TGmkList's inline constructor needs Vector<BdatInfo>; the size is not read
    // yet (placeholder: no fields declared)
    class BdatInfo {};
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x3d);
    // the step update calls while the gimmick is valid (the name is not the original's)
    void (TUnk_B6D5F8::*m_seq)(float dt);
    // fields: size from the stride 0x80: Vector<TUnk_B6D5F8>::resize fn_71005D3180
    void* m_portalEffect0;  // 0x58: fn_71005B8764 searches "ex_portal_01" in the field's effect pack (the name is not the original's)
    void* m_portalEffect1;  // 0x60: the same for "ex_portal_02" (the name is not the original's)
    unsigned int m_effectHandle0;  // 0x68: fn_71005B8870 kills or fades it out (the name is not the original's)
    unsigned int m_effectHandle1;  // 0x6c: likewise (the name is not the original's)
    gf::GF_OBJ_HANDLE* m_gob;  // 0x70: dispose destroys it unless it is -1 (the name is not the original's)
    float m_timer;  // 0x78: fn_71005B90D8 sets it from BDAT table 0x7B's member 0 at row 0x55; fn_71005B9268 counts it down (the name is not the original's)
    unsigned char pad_7c[0x4];

    // Placeholder names below: new in 3.0.1, nothing in 1.0.0's place names them. Members because their addresses sit
    // among this class's slots (dispose 0x71005B87E0 .. onGobEvent 0x71005B91A0) and they are its m_seq steps or are
    // called from them with this.
    // What it does (step; Vector<TUnk_B6D5F8>::resize installs it): finds the two portal effects in
    // gf::GfFieldManager's effect pack, then goes to fn_71005B9084.
    void fn_71005B8764(float);
    // What it does: destroys the game object (true: requests SCOM_DESTROY_GAME_OBJ, false: destroys it now) and
    // fades out (true) or kills (false) both effect handles; dispose and onGobEvent do its false case.
    void fn_71005B8870(bool);
    // What it does (called by fn_71005B9084): pops the game object (fn_71005B8D1C) and plays its effects.
    void fn_71005B8BC4();
    // What it does: creates the game object and its effects (true from fn_71005B90D8).
    void fn_71005B8D1C(bool);
    // What it does: true when the gimmick should pop its game object (BdatInfo conditions, distance to the
    // interest point).
    bool fn_71005B8E18();
    // What it does: true when the game object should go (its BdatInfo conditions fail or the interest point is
    // outside the invisible range).
    bool fn_71005B8FA0();
    // What it does (step): pops (fn_71005B8BC4) when fn_71005B8E18 says so, else depops (fn_71005B8870(true)) when
    // fn_71005B8FA0 says so.
    void fn_71005B9084(float);
    // What it does (step; GmkElevator::fn_71005B928C installs it): pops the game object (fn_71005B8D1C(true)), plays
    // the map's portal sound (map 0x3A: 2, 9: 0x10, 3: 0xD, else 0) and waits m_timer in fn_71005B9268.
    void fn_71005B90D8(float);
    // What it does (step): nothing (the end step fn_71005B9268 and GmkElevator::fn_71005B928C install).
    void fn_71005B919C(float);
    // What it does (step): counts m_timer down by dt, then goes to fn_71005B919C.
    void fn_71005B9268(float);
};
}  // namespace gmk

#endif
