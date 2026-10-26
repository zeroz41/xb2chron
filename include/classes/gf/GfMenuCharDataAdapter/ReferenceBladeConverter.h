#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_REFERENCEBLADECONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_REFERENCEBLADECONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"

namespace gf {
// table 0x7100B5B8D8
class GfMenuCharDataAdapter::ReferenceBladeConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    ReferenceBladeConverter(unsigned int index) : m_index(index) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    unsigned int m_index;  // GfMenuReference::getReferenceBladeID's (the name is not the original's)
};
}  // namespace gf

#endif
