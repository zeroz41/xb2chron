#ifndef CLASSES_GF_GFMENUITEMADAPTER_REFERENCEBLADEEQUIPCONVERTER_H
#define CLASSES_GF_GFMENUITEMADAPTER_REFERENCEBLADEEQUIPCONVERTER_H

#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuItemAdapter/IConverter.h"

namespace gf { class MenuItemInfo; }

namespace gf {
// table 0x7100B5CE88
class GfMenuItemAdapter::ReferenceBladeEquipConverter : public ::gf::GfMenuItemAdapter::IConverter {
public:
    ReferenceBladeEquipConverter(unsigned int reference, unsigned int slot) {
        m_slot = slot;  // stored before m_reference (the callers' register order shows it)
        m_reference = reference;
    }
    virtual ~ReferenceBladeEquipConverter();  // slot 0
    virtual void getItemInfo(gf::MenuItemInfo&);  // slot 2
    unsigned int m_reference;  // the GfMenuReference blade reference index
    unsigned int m_slot;       // the orb slot (0..2)
};
}  // namespace gf

#endif
