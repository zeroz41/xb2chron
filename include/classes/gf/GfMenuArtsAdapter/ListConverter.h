#ifndef CLASSES_GF_GFMENUARTSADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUARTSADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuArtsAdapter.h"
#include "classes/gf/GfMenuArtsAdapter/IConverter.h"
#include "classes/gf/GfMenuArtsList.h"

namespace gf {
// table 0x7100B5A010; the arts a GfMenuArtsList has at an index of the page shown (-1: its selected one), for a
// fixed driver
class GfMenuArtsAdapter::ListConverter : public ::gf::GfMenuArtsAdapter::IConverter {
public:
    ListConverter(GfMenuArtsList* list, int index, unsigned int driverId)
        : m_list(list), m_index(index), m_driverId(driverId) {
        m_list->addRef();
    }
    virtual ~ListConverter();  // slot 0
    virtual void getArtsInfo(MenuArtsInfo& info);  // slot 2
    virtual unsigned int getDriverId();  // slot 3
    GfMenuArtsList* m_list;  // referenced
    int m_index;
    unsigned int m_driverId;
};
}  // namespace gf

#endif
