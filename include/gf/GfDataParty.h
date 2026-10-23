#ifndef GF_GFDATAPARTY_H
#define GF_GFDATAPARTY_H

namespace gf {
// the party's game data (functions, by 1.0.0's symbols)
class GfDataParty {
public:
    // a party member's entry (6 bytes); the name is not the original's
    struct PartyMember {
        unsigned short m_driver;  // what GfMenuMercenariesAdapter::update_TeamNameRes reads as a driver (type 3)
        unsigned char pad_2[0x4];
    };
    // the member at an index of a party: 0 is the game data's (1.0.0's one-argument function), 1 and 2 two other
    // parties' kept elsewhere (3.0.1 added the second parameter; its name is not the original's)
    static PartyMember* getPartyMember(unsigned int index, unsigned int party);
    static bool isRideChar(unsigned int chara);
};
}  // namespace gf

#endif
