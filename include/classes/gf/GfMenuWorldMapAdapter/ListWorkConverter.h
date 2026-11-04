#ifndef CLASSES_GF_GFMENUWORLDMAPADAPTER_LISTWORKCONVERTER_H
#define CLASSES_GF_GFMENUWORLDMAPADAPTER_LISTWORKCONVERTER_H

#include "classes/gf/GfMenuWorldMapAdapter.h"
#include "classes/gf/GfMenuWorldMapAdapter/IConverter.h"
#include "classes/gf/GfMenuIDList.h"

namespace gf {
// table 0x7100B5E1A8 (in gf_menu_world_map_adapter's .data); 2.0.0's symbols name it. 1.0.0 has no such class
// (its match had named the table GfMenuMissionAdapter::MissionListConverter, which has the same slots).
// GfMenuWorldMapAdapter::createFromListWork makes it, update calls its slot 2 through IConverter: the map
// (MenuID::m_subId) a GfMenuIDList has at an index (-1: its selected one). Its members are inline (the world map
// file emits them after its own functions)
class GfMenuWorldMapAdapter::ListWorkConverter : public ::gf::GfMenuWorldMapAdapter::IConverter {
public:
    ListWorkConverter(GfMenuIDList* list, unsigned int index, bool onPage)
        : m_list(list), m_index(index), m_onPage(onPage) {
        m_list->addRef();
    }
    virtual ~ListWorkConverter() {  // slot 0
        if (m_list != nullptr) {
            m_list->release();
            m_list = nullptr;
        }
    }
    // slot 2: 0 past the list's end
    virtual unsigned int getMapId() {
        if (m_index == -1) {
            return m_list->getContents(m_list->getIndex(false)).m_subId;
        }
        if (m_onPage) {
            if (m_index < m_list->getSize()) {
                return m_list->getContents(m_list->getPageIndex(m_index)).m_subId;
            }
        } else if (m_index < m_list->getSize()) {
            return m_list->getContents(m_index).m_subId;
        }
        return 0;
    }
    GfMenuIDList* m_list;  // referenced
    unsigned int m_index;
    bool m_onPage;  // m_index is an index of the page shown (getPageIndex); the name is not the original's
};
}  // namespace gf

#endif
