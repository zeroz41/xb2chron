#ifndef CLASSES_GF_GFMENUWEAPONTYPEADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUWEAPONTYPEADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuWeaponTypeAdapter.h"

namespace gf {
// table none (its derived classes'): where a weapon type adapter's update takes its driver, weapon type and arts
// index from
class GfMenuWeaponTypeAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual unsigned int getDriverId() = 0;  // slot 2
    virtual unsigned int getWpnType() = 0;  // slot 3
    virtual unsigned int getArtsIndex() = 0;  // slot 4
};
}  // namespace gf

#endif
