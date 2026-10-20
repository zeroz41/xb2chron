#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_REFERENCEBLADEOWNERDRIVERCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_REFERENCEBLADEOWNERDRIVERCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"

namespace gf {
// table 0x7100B5B998
class GfMenuCharDataAdapter::ReferenceBladeOwnerDriverConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    virtual void getCharData(unsigned char&, unsigned int&);  // slot 0
};
}  // namespace gf

#endif
