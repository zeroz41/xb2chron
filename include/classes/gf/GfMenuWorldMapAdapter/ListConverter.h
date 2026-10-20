#ifndef CLASSES_GF_GFMENUWORLDMAPADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUWORLDMAPADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuWorldMapAdapter.h"

namespace gf {
// table 0x7100B5E180
class GfMenuWorldMapAdapter::ListConverter {
public:
    virtual ~ListConverter();  // slot 0
    virtual void getMapId();  // slot 2
};
}  // namespace gf

#endif
