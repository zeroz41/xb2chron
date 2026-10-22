#ifndef CLASSES_GF_GFMENUEVTHERTERADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUEVTHERTERADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuEvTherterAdapter.h"
#include "classes/gf/GfMenuEvTherterAdapter/IConverter.h"
#include "classes/gf/GfMenuIDList.h"

namespace gf {
// table 0x7100B5BC90; the id a GfMenuIDList has at an index of the page shown (-1: its selected one). It takes no
// reference to the list, and its members are inline (the file emits them after its own functions)
class GfMenuEvTherterAdapter::ListConverter : public ::gf::GfMenuEvTherterAdapter::IConverter {
public:
    ListConverter(GfMenuIDList* list, int index) : m_list(list), m_index(index) {}
    virtual ~ListConverter() {}  // slot 0: its D1 slot is the base's destructor
    // slot 2: 0 without a list or past its end
    virtual unsigned int getEvTheaterID() {
        if (m_list == nullptr) {
            return 0;
        }
        if (m_index == -1) {
            return m_list->getContents(m_list->getIndex(false)).m_id;
        }
        if (m_index >= m_list->getSize()) {
            return 0;
        }
        return m_list->getContents(m_list->getPageIndex(m_index)).m_id;
    }
    GfMenuIDList* m_list;
    int m_index;
};
}  // namespace gf

#endif
