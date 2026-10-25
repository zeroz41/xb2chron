#ifndef GF_GFDATAPARTY_H
#define GF_GFDATAPARTY_H

namespace gf {
// the party's part of the game data (GfDataParty::getSDataParty points at it); the name is not the original's
struct SDataParty {
    unsigned char pad_0[0x4C];
    unsigned short m_partyGauge;  // GfGameParty::getPartyGauge and setPartyGauge (300 full)
};

// the party's game data (functions, by 1.0.0's symbols)
class GfDataParty {
public:
    // a party member's entry (6 bytes); the name is not the original's
    struct PartyMember {
        unsigned short m_driver;  // what GfMenuMercenariesAdapter::update_TeamNameRes reads as a driver (type 3)
        // the driver's and its blade's place in the party's hierarchy (1.0.0's GfGameParty::getHierarchyDriver and
        // getHierarchyBlade read them; GfGameParty::getHandleByHierarchy looks them up)
        unsigned short m_hierarchyDriver;
        unsigned short m_hierarchyBlade;
    };
    // the member at an index of a party: 0 is the game data's (1.0.0's one-argument function), 1 and 2 two other
    // parties' kept elsewhere (3.0.1 added the second parameter; its name is not the original's)
    static PartyMember* getPartyMember(unsigned int index, unsigned int party);
    static bool isRideChar(unsigned int chara);
    static SDataParty* getSDataParty();
    // GfGameScene::isRide and isRideParty ask it about a party id
    static bool isNiaByakko(unsigned int id);
};
}  // namespace gf

#endif
