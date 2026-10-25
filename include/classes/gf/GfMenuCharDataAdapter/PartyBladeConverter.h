#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_PARTYBLADECONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_PARTYBLADECONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"

namespace gf {
// table 0x7100B5B788
class GfMenuCharDataAdapter::PartyBladeConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    virtual PartyBladeConverter* fromPartyBlade() { return this; }  // slot 3
    // (the names are not the original's)
    unsigned int m_party;  // 0: the chain attack's acting party member in battle
    unsigned int m_slot;   // the blade slot
    bool m_back;           // the back slots (getBladeIDFromPartyBackSlot)
    bool m_flag;           // the slot getters' flag
};
}  // namespace gf

#endif
