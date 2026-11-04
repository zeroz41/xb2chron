#ifndef CLASSES_GF_GFMENUBTLCHADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUBTLCHADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuBtlchAdapter/IConverter.h"
#include "classes/gf/GfMenuIDList.h"

namespace gf {
// table 0x7100B5A850; the id a list has at an index of the page shown (-1: its selected one), 0 without a list.
// 2.0.0's symbols name it (GfMenuBtlchAdapter::createFromList builds it). The list's class is inferred: an
// 8-byte entry whose first word is the id, as GfMenuIDList's (nothing calls createFromList to show the real one).
class GfMenuBtlchAdapter::ListConverter : public ::gf::GfMenuBtlchAdapter::IConverter {
public:
    ListConverter(GfMenuIDList* list, int index) : m_list(list), m_index(index) {}
    virtual unsigned int getBtlchID() {  // slot 2
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
    GfMenuIDList* m_list;  // not referenced
    int m_index;
};
}  // namespace gf

#endif
