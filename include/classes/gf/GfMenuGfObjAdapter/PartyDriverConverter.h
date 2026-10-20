#ifndef CLASSES_GF_GFMENUGFOBJADAPTER_PARTYDRIVERCONVERTER_H
#define CLASSES_GF_GFMENUGFOBJADAPTER_PARTYDRIVERCONVERTER_H

#include "classes/gf/GfMenuGfObjAdapter.h"
#include "classes/gf/GfMenuGfObjAdapter/IConverter.h"

namespace gf {
// table 0x7100B5C700
class GfMenuGfObjAdapter::PartyDriverConverter : public ::gf::GfMenuGfObjAdapter::IConverter {
public:
    virtual void getGfObjHandle();  // slot 0
    virtual void fromPartyDriver();  // slot 1
};
}  // namespace gf

#endif
