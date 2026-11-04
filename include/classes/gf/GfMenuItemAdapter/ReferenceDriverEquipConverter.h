#ifndef CLASSES_GF_GFMENUITEMADAPTER_REFERENCEDRIVEREQUIPCONVERTER_H
#define CLASSES_GF_GFMENUITEMADAPTER_REFERENCEDRIVEREQUIPCONVERTER_H

#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuItemAdapter/IConverter.h"

namespace gf { class MenuItemInfo; }

namespace gf {
// table 0x7100B5CE48 (the symbols leave it unnamed: 1.0.0's createFromReferenceDriverEquip builds this class, and
// 3.0.1's only builder GfMenuItemAdapter::createFromReferenceDriverEquip is that function, same code; its getItemInfo still reads the reference's driver)
class GfMenuItemAdapter::ReferenceDriverEquipConverter : public ::gf::GfMenuItemAdapter::IConverter {
public:
    ReferenceDriverEquipConverter(unsigned int reference, unsigned int slot) {
        m_slot = slot;  // stored before m_reference (the callers' register order shows it)
        m_reference = reference;
    }
    virtual ~ReferenceDriverEquipConverter();  // slot 0
    virtual void getItemInfo(gf::MenuItemInfo&);  // slot 2
    unsigned int m_reference;  // the GfMenuReference driver reference index
    unsigned int m_slot;       // the accessory slot (0..2; 0 is the DLC drivers' fixed one on menu layer 3)
};
}  // namespace gf

#endif
