#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_REFERENCEBLADEOWNERDRIVERCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_REFERENCEBLADEOWNERDRIVERCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"

namespace gf {
// table 0x7100B5B998
class GfMenuCharDataAdapter::ReferenceBladeOwnerDriverConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    ReferenceBladeOwnerDriverConverter(unsigned int blade) : m_blade(blade) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    unsigned int m_blade;  // GfMenuReference::getIraCharInfoFromFromID's (the name is not the original's)
};
}  // namespace gf

#endif
