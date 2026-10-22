#ifndef CLASSES_GF_GFMENUPOUCHADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUPOUCHADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuPouchAdapter.h"

namespace gf {
// table none (its derived classes'): where a pouch adapter's update takes its pouch and driver from
class GfMenuPouchAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual unsigned int getPouchIndex() = 0;  // slot 2
    virtual unsigned int getDriverId() = 0;  // slot 3
};
}  // namespace gf

#endif
