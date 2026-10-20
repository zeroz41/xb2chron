#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_BLADELISTCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_BLADELISTCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"

namespace gf {
// table 0x7100B5B7E8
class GfMenuCharDataAdapter::BladeListConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    virtual void getCharData(unsigned char&, unsigned int&);  // slot 0
};
}  // namespace gf

#endif
