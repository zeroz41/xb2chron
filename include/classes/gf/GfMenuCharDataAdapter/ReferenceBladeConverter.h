#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_REFERENCEBLADECONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_REFERENCEBLADECONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"

namespace gf {
// table 0x7100B5B8D8
class GfMenuCharDataAdapter::ReferenceBladeConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    virtual void getCharData(unsigned char&, unsigned int&);  // slot 0
};
}  // namespace gf

#endif
