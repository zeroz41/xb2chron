#ifndef CLASSES_GF_GFMENUWEAPONADAPTER_REFERENCECHIPCONVERTER_H
#define CLASSES_GF_GFMENUWEAPONADAPTER_REFERENCECHIPCONVERTER_H

#include "classes/gf/GfMenuWeaponAdapter.h"
#include "classes/gf/GfMenuWeaponAdapter/IConverter.h"

namespace gf {
// table 0x7100B5DD90; the weapon a core chip makes of the blade's (none without a chip)
class GfMenuWeaponAdapter::ReferenceChipConverter : public ::gf::GfMenuWeaponAdapter::IConverter {
public:
    ReferenceChipConverter(const ReferenceChip& chip) : m_chip(chip) {}
    virtual ~ReferenceChipConverter();  // slot 0
    virtual unsigned int getWeaponID();  // slot 2
    ReferenceChip m_chip;
};
}  // namespace gf

#endif
