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
    // its bdat row: complete because TGmkList's inline constructor needs Vector<BdatInfo>; the size is not read
    // yet (placeholder: no fields declared)
    class BdatInfo {};
    // its kind (TGmkList::getGmkType returns it; the name is not the original's)
    static const gmk::GmkType TYPE = gmk::GmkType(0x3d);
    unsigned char pad_48[0x38];  // fields: size from the stride 0x80: Vector<TUnk_B6D5F8>::resize fn_71005D3180
};
}  // namespace gmk

#endif
