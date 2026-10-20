#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_PARTYDRIVERCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_PARTYDRIVERCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"

namespace gf {
// table 0x7100B5B758
class GfMenuCharDataAdapter::PartyDriverConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    virtual void getCharData(unsigned char&, unsigned int&);  // slot 0
    virtual void fromPartyDriver();  // slot 2
};
}  // namespace gf

#endif
