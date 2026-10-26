#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_ENBOOKLISTCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_ENBOOKLISTCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"
#include "classes/gf/GfMenuIDList.h"

namespace gf {
// table 0x7100B5B848
class GfMenuCharDataAdapter::EnBookListConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    // an enemy book list's entry (its base enemy); index -1: the list's selected one
    EnBookListConverter(const GfMenuIDList* list, int index) : m_list(list), m_index(index) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    // (the names are not the original's)
    const GfMenuIDList* m_list;
    int m_index;
};
}  // namespace gf

#endif
