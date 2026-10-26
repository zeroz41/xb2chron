#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_BLADELISTCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_BLADELISTCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"
#include "classes/gf/GfMenuBladeList.h"

namespace gf {
// table 0x7100B5B7E8
class GfMenuCharDataAdapter::BladeListConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    // a blade list's entry; index -1: the list's selected one
    BladeListConverter(const GfMenuBladeList* list, int index) : m_list(list), m_index(index) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    // (the names are not the original's)
    const GfMenuBladeList* m_list;
    int m_index;
};
}  // namespace gf

#endif
