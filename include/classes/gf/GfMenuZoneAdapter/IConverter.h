#ifndef CLASSES_GF_GFMENUZONEADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUZONEADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuZoneAdapter.h"

namespace gf {
// table none (its derived classes'): where a zone adapter's update takes its zone from
class GfMenuZoneAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual unsigned int getZoneId() = 0;  // slot 2
};
}  // namespace gf

#endif
