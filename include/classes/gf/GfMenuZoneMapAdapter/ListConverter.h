#ifndef CLASSES_GF_GFMENUZONEMAPADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUZONEMAPADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuZoneMapAdapter.h"

namespace gf {
// table 0x7100B5E3B8
class GfMenuZoneMapAdapter::ListConverter {
public:
    virtual ~ListConverter();  // slot 0
    virtual void getMapId();  // slot 2
    virtual void getParam();  // slot 3
    virtual void isGroupMode();  // slot 4
};
}  // namespace gf

#endif
