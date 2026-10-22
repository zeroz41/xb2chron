#ifndef CLASSES_GF_GFMENUHANAPARTSADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUHANAPARTSADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuHanaPartsAdapter.h"

namespace gf {
// table none (its derived classes'): where a Hana part adapter's update takes its part from
class GfMenuHanaPartsAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual unsigned int getPartsId() = 0;  // slot 2
};
}  // namespace gf

#endif
