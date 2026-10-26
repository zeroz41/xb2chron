#ifndef CLASSES_GF_GFMENUMISSIONADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUMISSIONADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuMissionAdapter.h"
#include "classes/gf/GfMenuIDList.h"

namespace gf {
// table 0x7100B5D748
class GfMenuMissionAdapter::ListConverter : public ::gf::GfMenuMissionAdapter::IConverter {
public:
    ListConverter(GfMenuIDList* list, unsigned int index) : m_list(list), m_index(index) {
        m_list->addRef();
    }
    virtual ~ListConverter();  // slot 0
    virtual unsigned int getMissionId();  // slot 2
    GfMenuIDList* m_list;  // referenced
    unsigned int m_index;  // an index of the page shown (getPageIndex)
};
}  // namespace gf

#endif
