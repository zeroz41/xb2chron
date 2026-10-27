#ifndef CLASSES_GMK_TUNK_B6D590_H
#define CLASSES_GMK_TUNK_B6D590_H

#include "classes/gmk/AGmkBase.h"

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
    // its bdat row: complete because TGmkList's inline constructor needs Vector<BdatInfo>; the size is not read
    // yet (placeholder: no fields declared)
    class BdatInfo {};
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x3c);
    unsigned char pad_48[0x30];  // fields: size from the stride 0x78: Vector<TUnk_B6D590>::resize fn_71005D107C/fn_71005D15A4
};
}  // namespace gmk

#endif
