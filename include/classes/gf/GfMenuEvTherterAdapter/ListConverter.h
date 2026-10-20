#ifndef CLASSES_GF_GFMENUEVTHERTERADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUEVTHERTERADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuEvTherterAdapter.h"

namespace gf {
// table 0x7100B5BC90
class GfMenuEvTherterAdapter::ListConverter {
public:
    virtual ~ListConverter();  // slot 0
    virtual void getEvTheaterID();  // slot 2
};
}  // namespace gf

#endif
