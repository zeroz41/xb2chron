#ifndef CLASSES_GF_GFMENUWEAPONTYPEADAPTER_REFERENCEDRIVERCONVERTER_H
#define CLASSES_GF_GFMENUWEAPONTYPEADAPTER_REFERENCEDRIVERCONVERTER_H

#include "classes/gf/GfMenuWeaponTypeAdapter.h"

namespace gf {
// table 0x7100B5E0A0
class GfMenuWeaponTypeAdapter::ReferenceDriverConverter {
public:
    virtual ~ReferenceDriverConverter();  // slot 0
    virtual void getDriverId();  // slot 2
    virtual void getWpnType();  // slot 3
    virtual void getArtsIndex();  // slot 4
};
}  // namespace gf

#endif
