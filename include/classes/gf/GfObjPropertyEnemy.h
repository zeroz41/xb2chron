#ifndef CLASSES_GF_GFOBJPROPERTYENEMY_H
#define CLASSES_GF_GFOBJPROPERTYENEMY_H

#include "classes/gf/GfObjProperty.h"

namespace gf {
// table 0x7100B6A2E8; an enemy's property (GfObjProperty::create's for type 5, 0x160 bytes; GfObjProperty::getEnemy
// returns the property itself as one)
class GfObjPropertyEnemy : public ::gf::GfObjProperty {
public:
    virtual ~GfObjPropertyEnemy();  // slot 0
    unsigned char pad_90[0x4C];
    // the elemental combo on the enemy and its level (1.0.0's GfMenuElementComboAdapter::getTargetElementComboId
    // and getTargetElementComboLv return them; the field names are not the original's)
    unsigned int m_elementComboId;
    unsigned char pad_E0[0x8];
    unsigned int m_elementComboLv;
};
}  // namespace gf

#endif
