#ifndef CLASSES_GF_GFMENUPOUCHADAPTER_REFERENCEDRIVERCONVERTER_H
#define CLASSES_GF_GFMENUPOUCHADAPTER_REFERENCEDRIVERCONVERTER_H

#include "classes/gf/GfMenuPouchAdapter.h"

namespace gf {
// table 0x7100B5D850
class GfMenuPouchAdapter::ReferenceDriverConverter {
public:
    virtual ~ReferenceDriverConverter();  // slot 0
    virtual void getPouchIndex();  // slot 2
    virtual void getDriverId();  // slot 3
};
}  // namespace gf

#endif
