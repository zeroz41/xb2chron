#ifndef CLASSES_GF_GFMENUZONEMAPADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUZONEMAPADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuZoneMapAdapter.h"

namespace gf {
// table none (its derived classes'): where a zone map adapter's update takes its map from (1.0.0's
// createFromCoverter takes one)
class GfMenuZoneMapAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual unsigned int getMapId() = 0;  // slot 2
    virtual unsigned int getParam() = 0;  // slot 3
    virtual bool isGroupMode() = 0;  // slot 4
};
}  // namespace gf

#endif
