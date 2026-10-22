#ifndef CLASSES_GF_GFMENUEVTHERTERADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUEVTHERTERADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuEvTherterAdapter.h"

namespace gf {
// table none (its derived classes'): where an event theater adapter's update takes its id from
class GfMenuEvTherterAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual unsigned int getEvTheaterID() = 0;  // slot 2
};
}  // namespace gf

#endif
