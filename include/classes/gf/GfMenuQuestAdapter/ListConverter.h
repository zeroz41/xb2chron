#ifndef CLASSES_GF_GFMENUQUESTADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUQUESTADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuQuestAdapter.h"
#include "classes/gf/GfMenuQuestAdapter/IConverter.h"
#include "classes/gf/GfMenuQuestList.h"

namespace gf {
// table 0x7100B5D8D0; the quest a GfMenuQuestList has at an index of the page shown (-1: its selected one); it takes a
// reference to the list
class GfMenuQuestAdapter::ListConverter : public ::gf::GfMenuQuestAdapter::IConverter {
public:
    ListConverter(GfMenuQuestList* list, int index) : m_list(list), m_index(index) { m_list->addRef(); }
    virtual ~ListConverter() {  // slot 0
        if (m_list != nullptr) {
            m_list->release();
            m_list = nullptr;
        }
    }
    // slot 2: unchanged without a list or past its page
    virtual void getQuestID(QuestID& id) {
        if (m_list == nullptr) {
            return;
        }
        // the halves one by one, as the original copies them
        if (m_index == -1) {
            const QuestID& selected = m_list->getContents(m_list->getIndex(false));
            id.m_id = selected.m_id;
            id.m_achieveId = selected.m_achieveId;
            return;
        }
        if (m_index >= (int)m_list->getPageSize()) {
            return;
        }
        const QuestID& contents = m_list->getContents(m_list->getPageIndex(m_index));
        id.m_id = contents.m_id;
        id.m_achieveId = contents.m_achieveId;
    }
    GfMenuQuestList* m_list;
    int m_index;
};
}  // namespace gf

#endif
