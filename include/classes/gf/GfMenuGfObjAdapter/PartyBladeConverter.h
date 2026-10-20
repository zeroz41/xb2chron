#ifndef CLASSES_GF_GFMENUGFOBJADAPTER_PARTYBLADECONVERTER_H
#define CLASSES_GF_GFMENUGFOBJADAPTER_PARTYBLADECONVERTER_H

#include "classes/gf/GfMenuGfObjAdapter.h"
#include "classes/gf/GfMenuGfObjAdapter/IConverter.h"

namespace gf {
// table 0x7100B5C728
class GfMenuGfObjAdapter::PartyBladeConverter : public ::gf::GfMenuGfObjAdapter::IConverter {
public:
    virtual void getGfObjHandle();  // slot 0
    virtual void fromPartyBlade();  // slot 2
};
}  // namespace gf

#endif
