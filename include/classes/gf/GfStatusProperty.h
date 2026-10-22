#ifndef CLASSES_GF_GFSTATUSPROPERTY_H
#define CLASSES_GF_GFSTATUSPROPERTY_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace gf {
// table 0x7100B553F0; counted (GfGameParty::createPartyStatusProperty holds one by IntrusivePtr and sets its
// count to 1): an object's hit points
class GfStatusProperty : public mm::mtl::ReferenceObject {
public:
    virtual ~GfStatusProperty();  // slot 0

    unsigned char pad_c[0x4];  // createPartyStatusProperty sets it to the hit points it gives, as the next two
    unsigned int m_maxHp;      // FallDamagePlugin::onDeactivate takes its fall damage as a share of it
    unsigned int m_hp;         // GfComProperty::procMsgObjectDamage takes damage from it (0: dead)
    unsigned char pad_18[0x8];
};
}  // namespace gf

#endif
