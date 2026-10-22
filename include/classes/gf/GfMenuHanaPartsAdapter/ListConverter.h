#ifndef CLASSES_GF_GFMENUHANAPARTSADAPTER_LISTCONVERTER_H
#define CLASSES_GF_GFMENUHANAPARTSADAPTER_LISTCONVERTER_H

#include "classes/gf/GfMenuHanaPartsAdapter.h"
#include "classes/gf/GfMenuHanaPartsAdapter/IConverter.h"
#include "classes/gf/GfMenuIDList.h"

namespace gf {
// table 0x7100B5C9D0; the id a GfMenuIDList has at an index of the page shown (-1: its selected one)
class GfMenuHanaPartsAdapter::ListConverter : public ::gf::GfMenuHanaPartsAdapter::IConverter {
public:
    ListConverter(GfMenuIDList* list, int index) : m_list(list), m_index(index) {
        m_list->addRef();
    }
    virtual ~ListConverter();  // slot 0
    virtual unsigned int getPartsId();  // slot 2
    GfMenuIDList* m_list;  // referenced
    int m_index;
};
}  // namespace gf

#endif
