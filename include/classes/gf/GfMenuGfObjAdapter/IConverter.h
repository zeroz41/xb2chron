#ifndef CLASSES_GF_GFMENUGFOBJADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUGFOBJADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuGfObjAdapter.h"

namespace gf {
// table none (its derived classes')
class GfMenuGfObjAdapter::IConverter {
public:
    virtual void getGfObjHandle() = 0;  // slot 0
    virtual void fromPartyDriver();  // slot 1
    virtual void fromPartyBlade();  // slot 2
};
}  // namespace gf

#endif
