#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_PARTYBLADECONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_PARTYBLADECONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter.h"
#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"

namespace gf {
// table 0x7100B5B788
class GfMenuCharDataAdapter::PartyBladeConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    virtual void getCharData(unsigned char&, unsigned int&);  // slot 0
    virtual void fromPartyBlade();  // slot 3
};
}  // namespace gf

#endif
