#ifndef CLASSES_GF_GFMENUWORLDMAPADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUWORLDMAPADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuWorldMapAdapter.h"

namespace gf {
// table none (its derived classes'): where a world map adapter's update takes its map from
class GfMenuWorldMapAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual unsigned int getMapId() = 0;  // slot 2
};
}  // namespace gf

#endif
