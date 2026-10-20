#ifndef CLASSES_GF_GFMENUHANAPARTSADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUHANAPARTSADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuHanaPartsAdapter.h"

namespace gf {
// table 0x7100B5C9D0
class GfMenuHanaPartsAdapter::ListConverter {
public:
    virtual ~ListConverter();  // slot 0
    virtual void getPartsId();  // slot 2
};
}  // namespace gf

#endif
