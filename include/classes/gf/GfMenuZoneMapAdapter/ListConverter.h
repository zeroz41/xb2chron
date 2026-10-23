#ifndef CLASSES_GF_GFMENUZONEMAPADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUZONEMAPADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuZoneMapAdapter.h"
#include "classes/gf/GfMenuZoneMapAdapter/IConverter.h"
#include "classes/gf/GfMenuZoneMapList.h"

namespace gf {
// table 0x7100B5E3B8; what a GfMenuZoneMapList has at an index (or its selection)
class GfMenuZoneMapAdapter::ListConverter : public ::gf::GfMenuZoneMapAdapter::IConverter {
public:
    ListConverter(GfMenuZoneMapList* list, unsigned int index, bool onPage)
        : m_list(list), m_index(index), m_onPage(onPage) {
        m_list->addRef();
    }
    virtual ~ListConverter();  // slot 0
    virtual unsigned int getMapId();  // slot 2
    virtual unsigned int getParam();  // slot 3
    virtual bool isGroupMode();  // slot 4
    GfMenuZoneMapList* m_list;  // referenced
    unsigned int m_index;       // -1: the list's selection
    // m_index is a place on the page shown (getPageIndex), not a content index (the name is not the original's)
    bool m_onPage;
};
}  // namespace gf

#endif
