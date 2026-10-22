#ifndef CLASSES_GF_GFMENUHANAADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUHANAADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuHanaAdapter.h"

namespace gf {
// table none (its derived classes'): where a Hana adapter's update takes its blade from
class GfMenuHanaAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual unsigned int getHanaId() = 0;  // slot 2
};
}  // namespace gf

#endif
