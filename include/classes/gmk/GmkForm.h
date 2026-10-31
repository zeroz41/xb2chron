#ifndef CLASSES_GMK_GMKFORM_H
#define CLASSES_GMK_GMKFORM_H

#include "mm/Vec3.h"

namespace gmk { class GmkSet; }

namespace gmk {
// no table; the class and member names come from the symbols (GmkForm::create, dispose, getPosRotY,
// validatePosRotY); the fields' names are not the original's
class GmkForm {
public:
    // which party formation gimmick of a set to take (gf callers build it: GfGameSalvage::applyPartyForm,
    // SCOM_CREATE_PARTY_OBJ::exec; the field names are not the original's)
    struct CreateInfo {
        const GmkSet* m_set;    // the gimmick set
        unsigned int m_index;   // the gimmick's index in the set's list
        // 0xc: takes the kind-26 formation list (with its kind-27 npcs) instead of the kind-24 one (meaning unknown)
        bool pad_c;
    };
    // all positions zero; creates from info when given one
    GmkForm(const CreateInfo* info);
    // from the formation gimmick the info names; false when there is none
    bool create(const CreateInfo& info);
    // from a formation gimmick and its bound npc kind (instantiated for TGmkFormPc<24/26>; defined elsewhere)
    template <typename T, typename U>
    bool create(const T& form);
    // one position and rotation; checks them (validatePosRotY); true
    bool create(const mm::Vec3& pos, float rotY);
    void dispose();
    // the position and rotation at index
    void getPosRotY(mm::Vec3& pos, float& rotY, unsigned int index) const;
    void validatePosRotY();

    int pad_0;  // 1 once created, 0 after dispose
    unsigned char pad_4[0xc];
    mm::Vec3 pad_10[6];  // 0x10: positions by index (create sets the first)
    float pad_70[6];  // 0x70: rotations by index (create sets the first; the count is not known, taken as 6)
};
}  // namespace gmk

#endif
