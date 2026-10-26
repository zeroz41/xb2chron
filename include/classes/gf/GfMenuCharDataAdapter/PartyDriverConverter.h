#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_PARTYDRIVERCONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_PARTYDRIVERCONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"

namespace gf {
// table 0x7100B5B758
class GfMenuCharDataAdapter::PartyDriverConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    PartyDriverConverter(unsigned char party) : m_party(party) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    virtual PartyDriverConverter* fromPartyDriver();  // slot 2
    unsigned int m_party;  // GfGameParty::getHandleDriver's first argument (the name is not the original's)
};
}  // namespace gf

#endif
