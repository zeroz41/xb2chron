#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"

namespace gf {
// table none (its derived classes')
class GfMenuCharDataAdapter::IConverter {
public:
    virtual void getCharData(unsigned char&, unsigned int&) = 0;  // slot 0
    virtual void fromGfObj();  // slot 1
    virtual void fromPartyDriver();  // slot 2
    virtual void fromPartyBlade();  // slot 3
};
}  // namespace gf

#endif
