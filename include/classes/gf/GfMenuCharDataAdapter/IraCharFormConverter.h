#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_IRACHARFORMCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_IRACHARFORMCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"

namespace gf {
// table 0x7100B5B998; 2.0.0's symbols name it
class GfMenuCharDataAdapter::IraCharFormConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    IraCharFormConverter(unsigned int blade) : m_blade(blade) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    unsigned int m_blade;  // GfMenuReference::getIraCharInfoFromFromID's (the name is not the original's)
};
}  // namespace gf

#endif
