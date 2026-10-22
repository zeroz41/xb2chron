#ifndef CLASSES_GF_GFMENUEXCTASKADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUEXCTASKADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuExcTaskAdapter.h"
#include "classes/gf/GfMenuExcTaskAdapter/IConverter.h"
#include "classes/gf/GfMenuIDList.h"

namespace gf {
// table 0x7100B5BD00; the id a GfMenuIDList has at an index of the page shown (-1: its selected one)
class GfMenuExcTaskAdapter::ListConverter : public ::gf::GfMenuExcTaskAdapter::IConverter {
public:
    ListConverter(GfMenuIDList* list, unsigned int index) : m_list(list), m_index(index) {
        m_list->addRef();
    }
    virtual ~ListConverter();  // slot 0
    virtual void getTaskID(unsigned int& taskId);  // slot 2
    virtual void fromList();  // slot 3; does nothing
    GfMenuIDList* m_list;  // referenced
    unsigned int m_index;
};
}  // namespace gf

#endif
