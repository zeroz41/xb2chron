#ifndef CLASSES_GF_GFMENUWORLDMAPADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUWORLDMAPADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuWorldMapAdapter.h"
#include "classes/gf/GfMenuWorldMapAdapter/IConverter.h"
#include "classes/gf/GfMenuIDList.h"

namespace gf {
// table 0x7100B5E180; the id a GfMenuIDList has at an index (-1: its selected one). Its members are inline (the
// file emits them after its own functions)
class GfMenuWorldMapAdapter::ListConverter : public ::gf::GfMenuWorldMapAdapter::IConverter {
public:
    ListConverter(GfMenuIDList* list, unsigned int index, bool onPage) : m_list(list), m_index(index), m_onPage(onPage) {
        m_list->addRef();
    }
    virtual ~ListConverter() {  // slot 0
        if (m_list != nullptr) {
            m_list->release();
            m_list = nullptr;
        }
    }
    // slot 2: 0 past the list's end
    virtual unsigned int getMapId() {
        if (m_index == -1) {
            return m_list->getContents(m_list->getIndex(false)).m_id;
        }
        if (m_onPage) {
            if (m_index < m_list->getSize()) {
                return m_list->getContents(m_list->getPageIndex(m_index)).m_id;
            }
        } else if (m_index < m_list->getSize()) {
            return m_list->getContents(m_index).m_id;
        }
        return 0;
    }
    GfMenuIDList* m_list;  // referenced
    unsigned int m_index;
    bool m_onPage;  // m_index is an index of the page shown (getPageIndex); the name is not the original's
};
}  // namespace gf

#endif
