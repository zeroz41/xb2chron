#ifndef CLASSES_GF_GFMENUELEMENTCOMBOADAPTER_REFERENCEROUTECONVERTER_H
#define CLASSES_GF_GFMENUELEMENTCOMBOADAPTER_REFERENCEROUTECONVERTER_H

#include "classes/gf/GfMenuElementComboAdapter.h"
#include "classes/gf/GfMenuElementComboAdapter/IConverter.h"

namespace gf {
// table 0x7100B5BBF8; a route of GfMenuReference's elemental combo
class GfMenuElementComboAdapter::ReferenceRouteConverter : public ::gf::GfMenuElementComboAdapter::IConverter {
public:
    explicit ReferenceRouteConverter(unsigned int routeNo) : m_routeNo(routeNo) {}
    virtual unsigned int getElementComboRouteNo();  // slot 2
    // the route's combo while the target enemy has a combo on it, else 0
    virtual unsigned int getElementComboId();  // slot 3
    unsigned int m_routeNo;
};
}  // namespace gf

#endif
