#ifndef CLASSES_GF_GFMENUWEAPONADAPTER_REFERENCECHIPCONVERTER_H
#define CLASSES_GF_GFMENUWEAPONADAPTER_REFERENCECHIPCONVERTER_H

#include "classes/gf/GfMenuWeaponAdapter.h"

namespace gf {
// table 0x7100B5DD90
class GfMenuWeaponAdapter::ReferenceChipConverter {
public:
    virtual ~ReferenceChipConverter();  // slot 0
    virtual void getWeaponID();  // slot 2
};
}  // namespace gf

#endif
