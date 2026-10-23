#ifndef CLASSES_GF_GFMENUARTSADAPTER_LISTREFERENCEDRIVERCONVERTER_H
#define CLASSES_GF_GFMENUARTSADAPTER_LISTREFERENCEDRIVERCONVERTER_H

#include "classes/gf/GfMenuArtsAdapter.h"
#include "classes/gf/GfMenuArtsAdapter/IConverter.h"
#include "classes/gf/GfMenuArtsList.h"

namespace gf {
// table 0x7100B5A040; the arts a GfMenuArtsList has at an index of the page shown (-1: its selected one), for the
// driver GfMenuReference has at a reference index
class GfMenuArtsAdapter::ListReferenceDriverConverter : public ::gf::GfMenuArtsAdapter::IConverter {
public:
    ListReferenceDriverConverter(GfMenuArtsList* list, int index, unsigned int reference)
        : m_list(list), m_index(index), m_reference(reference) {
        m_list->addRef();
    }
    virtual ~ListReferenceDriverConverter();  // slot 0
    virtual void getArtsInfo(MenuArtsInfo& info);  // slot 2
    virtual unsigned int getDriverId();  // slot 3
    GfMenuArtsList* m_list;  // referenced
    int m_index;
    unsigned int m_reference;  // GfMenuReference::getReferenceDriverID's index
};
}  // namespace gf

#endif
