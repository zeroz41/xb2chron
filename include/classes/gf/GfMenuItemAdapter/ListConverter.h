#ifndef CLASSES_GF_GFMENUITEMADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUITEMADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuItemAdapter.h"
#include "classes/gf/GfMenuItemAdapter/IConverter.h"

namespace gf { class MenuItemInfo; }

namespace gf {
// table 0x7100B5CD88
class GfMenuItemAdapter::ListConverter : public ::gf::GfMenuItemAdapter::IConverter {
public:
    ListConverter(GfMenuItemList* list, int index) : m_list(list), m_index(index) {
        m_list->addRef();
    }
    virtual ~ListConverter();  // slot 0
    virtual void getItemInfo(gf::MenuItemInfo&);  // slot 2
    virtual ListConverter* fromList();  // slot 3
    GfMenuItemList* m_list;  // referenced
    unsigned int m_index;  // -1: the list's selected item (compared unsigned with the list's size)
};
}  // namespace gf

#endif
