#ifndef CLASSES_GF_GFSTATUSPROPERTY_H
#define CLASSES_GF_GFSTATUSPROPERTY_H

#include "classes/mm/mtl/ReferenceObject.h"

namespace gf {
// table 0x7100B553F0; counted (GfGameParty::createPartyStatusProperty holds one by IntrusivePtr and sets its
// count to 1): an object's hit points
class GfStatusProperty : public mm::mtl::ReferenceObject {
public:
    // GfGameParty::createPartyStatusProperty makes one with the hit points it gives (inline there)
    GfStatusProperty(unsigned int hp) : m_baseHp(hp), m_maxHp(hp), m_hp(hp), pad_18() {}
    // the table's slot 0 holds ReferenceObject's destructor (the module folded this one into it): inline
    virtual ~GfStatusProperty() {}  // slot 0

    // set to the hit points it is made with, as the next two (the name is not the original's)
    unsigned int m_baseHp;
    unsigned int m_maxHp;      // FallDamagePlugin::onDeactivate takes its fall damage as a share of it
    unsigned int m_hp;         // GfComProperty::procMsgObjectDamage takes damage from it (0: dead)
    unsigned char pad_18[0x8];
};
}  // namespace gf

#endif
