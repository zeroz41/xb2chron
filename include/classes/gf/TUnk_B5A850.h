#ifndef CLASSES_GF_TUNK_B5A850_H
#define CLASSES_GF_TUNK_B5A850_H

#include "classes/gf/TUnk_B5A648/IConverter.h"
#include "classes/gf/GfMenuIDList.h"

namespace gf {
// table 0x7100B5A850; the id a list has at an index of the page shown (-1: its selected one), 0 without a list.
// The symbols leave the class unnamed (TUnk_B5A648::fn_71003349CC builds it). The list's class is inferred: an
// 8-byte entry whose first word is the id, as GfMenuIDList's (nothing calls fn_71003349CC to show the real one).
class TUnk_B5A850 : public ::gf::TUnk_B5A648::IConverter {
public:
    TUnk_B5A850(GfMenuIDList* list, int index) : m_list(list), m_index(index) {}
    virtual unsigned int fn_7100334D68() {  // slot 2
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
