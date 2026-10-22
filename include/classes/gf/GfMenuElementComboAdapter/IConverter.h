#ifndef CLASSES_GF_GFMENUELEMENTCOMBOADAPTER_ICONVERTER_H
#define CLASSES_GF_GFMENUELEMENTCOMBOADAPTER_ICONVERTER_H

#include "classes/gf/GfMenuElementComboAdapter.h"

namespace gf {
// table none (its derived classes'): where an element combo adapter takes its route and combo from
class GfMenuElementComboAdapter::IConverter {
public:
    virtual ~IConverter() {}  // slot 0
    virtual unsigned int getElementComboRouteNo() = 0;  // slot 2
    virtual unsigned int getElementComboId() = 0;  // slot 3
};
}  // namespace gf

#endif
