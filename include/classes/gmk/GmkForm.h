#ifndef CLASSES_GMK_GMKFORM_H
#define CLASSES_GMK_GMKFORM_H

#include "mm/Vec3.h"
#include "classes/gmk/IGmkList.h"

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
    // from a formation gimmick and its bound npc kind (instantiated for TGmkFormPc<24/26>): its own position first,
    // then those of its bound TGmkFormPcnpc list's elements, six at most
    template <typename T, typename U>
    bool create(const T& form);
    // one position and rotation; checks them (validatePosRotY); true
    bool create(const mm::Vec3& pos, float rotY);
    void dispose();
    // places the party at its positions (GfGameSalvage::applyPartyForm passes 4.0f; meaning of the value unknown)
    void apply(float);
    // the position and rotation at index
    void getPosRotY(mm::Vec3& pos, float& rotY, unsigned int index) const;
    void validatePosRotY();

    unsigned int pad_0;  // how many positions it holds (create<T, U> compares it unsigned); 0 after dispose
    unsigned char pad_4[0xc];
    mm::Vec3 pad_10[6];  // 0x10: positions by index (create sets the first)
    float pad_70[6];  // 0x70: rotations by index (create sets the first; the count is not known, taken as 6)
};

template <typename T, typename U>
bool GmkForm::create(const T& form) {
    dispose();
    pad_0 = form.getData()->m_npcLast - form.getData()->m_npcFirst + 1;
    if (pad_0 > 6) {
        pad_0 = 6;
    } else if (pad_0 == 0) {
        return false;
    }
    const typename T::Data* data = form.getData();
    pad_10[0].x = data->m_posX;
    pad_10[0].y = data->m_posY;
    pad_10[0].z = data->m_posZ;
    pad_70[0] = data->m_rotY;
    for (unsigned int i = 1; i < pad_0; i++) {
        const IGmkList* list = form.getBindedFormPcnpcList();
        unsigned int index = form.getData()->m_npcFirst + i - 1;
        // the original asks the list's count and does not use it
        list->getInstNum();
        const typename U::Data* npc = static_cast<const U*>(list->getInst(index))->getData();
        mm::Vec3& pos = pad_10[i];
        pos.x = npc->m_posX;
        pos.y = npc->m_posY;
        pos.z = npc->m_posZ;
        pad_70[i] = npc->m_rotY;
    }
    validatePosRotY();
    return true;
}
}  // namespace gmk

#endif
