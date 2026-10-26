#ifndef CLASSES_GF_GFMENUCHARDATAADAPTER_PARTYBLADECONVERTER_H
#define CLASSES_GF_GFMENUCHARDATAADAPTER_PARTYBLADECONVERTER_H

#include "classes/gf/GfMenuCharDataAdapter/IConverter.h"
#include "classes/gf/GfMenuReference.h"
#include "classes/gf/GfMenuManager.h"

namespace gf {
// table 0x7100B5B788
class GfMenuCharDataAdapter::PartyBladeConverter : public ::gf::GfMenuCharDataAdapter::IConverter {
public:
    PartyBladeConverter(unsigned char party, int slot, bool back, bool flag)
        : m_party(party), m_slot(slot), m_back(back), m_flag(flag) {}
    virtual void getCharData(unsigned char& objType, unsigned int& objId);  // slot 0
    virtual PartyBladeConverter* fromPartyBlade();  // slot 3
    // party 0: the chain attack's acting party member in battle (getParty); the names are not the original's
    unsigned int getParty() const {
        unsigned int party = m_party;
        if (party == 0) {
            if (GfMenuManager::isBattleState(3)) {
                int id = GfMenuReference::getChainAttackActionPartyID();
                party = id >= 0 && static_cast<unsigned int>(id) < 3 ? id : 0;
            } else {
                party = 0;
            }
        }
        return party;
    }
    unsigned int m_party;
    int m_slot;    // the blade slot
    bool m_back;   // the back slots (getBladeIDFromPartyBackSlot)
    bool m_flag;   // the slot getters' flag
};
}  // namespace gf

#endif
