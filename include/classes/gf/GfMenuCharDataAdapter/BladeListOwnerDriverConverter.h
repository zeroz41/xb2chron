#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_BLADELISTOWNERDRIVERCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_BLADELISTOWNERDRIVERCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"
#include "classes/gf/GfMenuBladeList.h"

namespace gf {
// table 0x7100B5B938 (2.0.0's symbols name it): a GfMenuCharDataAdapter converter new in 3.0.1, built only by
// GfMenuCharDataAdapter::createFromBladeListOwnerDriver: the driver who created a blade list's entry
// (GfDataBlade::getCreator).
class GfMenuCharDataAdapter::BladeListOwnerDriverConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    // index -1: the list's selected one
    BladeListOwnerDriverConverter(const GfMenuBladeList* list, int index) : m_list(list), m_index(index) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    // (the names are not the original's)
    const GfMenuBladeList* m_list;
    int m_index;
};
}  // namespace gf

#endif
