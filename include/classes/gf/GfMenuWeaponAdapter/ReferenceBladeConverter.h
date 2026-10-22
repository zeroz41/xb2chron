#ifndef CLASSES_GF_GFMENUWEAPONADAPTER_REFERENCEBLADECONVERTER_H
#define CLASSES_GF_GFMENUWEAPONADAPTER_REFERENCEBLADECONVERTER_H

#include "classes/gf/GfMenuWeaponAdapter.h"
#include "classes/gf/GfMenuWeaponAdapter/IConverter.h"
#include "classes/gf/DataParamAcc.h"
#include "classes/gf/GfMenuReference.h"

namespace gf {
// table 0x7100B5DD68; the weapon the blade GfMenuReference has at a reference index holds
class GfMenuWeaponAdapter::ReferenceBladeConverter : public ::gf::GfMenuWeaponAdapter::IConverter {
public:
    ReferenceBladeConverter(unsigned int reference) : m_reference(reference) {}
    virtual ~ReferenceBladeConverter() {}  // slot 0; its D2 folds into IConverter's
    virtual unsigned int getWeaponID() {  // slot 2
        DataParamAcc acc(4, GfMenuReference::getReferenceBladeID(m_reference), GimmickType(0));
        unsigned int weapon = 0;
        if (acc.isValid()) {
            weapon = acc.getEquipWeapon(-1, false);
        }
        return weapon;
    }
    unsigned int m_reference;  // GfMenuReference::getReferenceBladeID's index
};
}  // namespace gf

#endif
