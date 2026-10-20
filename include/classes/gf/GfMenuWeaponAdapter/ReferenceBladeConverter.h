#ifndef CLASSES_GF_GFMENUWEAPONADAPTER_REFERENCEBLADECONVERTER_H
#define CLASSES_GF_GFMENUWEAPONADAPTER_REFERENCEBLADECONVERTER_H

#include "classes/gf/GfMenuWeaponAdapter.h"

namespace gf {
// table 0x7100B5DD68
class GfMenuWeaponAdapter::ReferenceBladeConverter {
public:
    virtual ~ReferenceBladeConverter();  // slot 0
    virtual void getWeaponID();  // slot 2
};
}  // namespace gf

#endif
