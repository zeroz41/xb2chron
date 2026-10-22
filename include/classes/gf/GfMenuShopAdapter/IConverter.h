#ifndef CLASSES_GF_GFMENUSHOPADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUSHOPADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuShopAdapter.h"

namespace gf {
// table none (its derived classes'): where a shop adapter's update takes its id from
class GfMenuShopAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual unsigned int getShopID() = 0;  // slot 2
};
}  // namespace gf

#endif
