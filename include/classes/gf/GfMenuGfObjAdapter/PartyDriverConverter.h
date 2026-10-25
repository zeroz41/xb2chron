#ifndef CLASSES_GF_GFMENUGFOBJADAPTER_PARTYDRIVERCONVERTER_H
#define CLASSES_GF_GFMENUGFOBJADAPTER_PARTYDRIVERCONVERTER_H

#include "classes/gf/GfMenuGfObjAdapter.h"
#include "classes/gf/GfMenuGfObjAdapter/IConverter.h"
#include "classes/gf/GfGameParty.h"

namespace gf {
// table 0x7100B5C700
class GfMenuGfObjAdapter::PartyDriverConverter : public ::gf::GfMenuGfObjAdapter::IConverter {
public:
    explicit PartyDriverConverter(unsigned char driver) : m_driver(driver) {}
    virtual GF_OBJ_HANDLE* getGfObjHandle() { return GfGameParty::getHandleDriver(m_driver, 0); }  // slot 0
    virtual PartyDriverConverter* fromPartyDriver() { return this; }  // slot 1
    unsigned int m_driver;  // the party driver (changePartyDriver sets it; the name is not the original's)
};
}  // namespace gf

#endif
