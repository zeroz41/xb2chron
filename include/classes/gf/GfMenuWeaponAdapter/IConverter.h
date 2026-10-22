#ifndef CLASSES_GF_GFMENUWEAPONADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUWEAPONADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuWeaponAdapter.h"

namespace gf {
// table none (its derived classes'): where a weapon adapter's update takes its weapon from
class GfMenuWeaponAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual unsigned int getWeaponID() = 0;  // slot 2
};
}  // namespace gf

#endif
