#ifndef GF_GFDATAPARTY_H
#define GF_GFDATAPARTY_H

namespace mm { class Vec3; }

namespace gf {
// the party's part of the game data (GfDataParty::getSDataParty points at it); the name is not the original's
struct SDataParty {
    unsigned char pad_0[0x40];
    unsigned int m_leader;  // 0x40: GfDataParty::isLeader compares a character with it (the name is not the original's)
    unsigned char pad_44[0x8];
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
    // a blade's fixed party handle: driver * 5 + index + 3
    static unsigned int getFixedHandleForBlade(unsigned int driver, int index);
    static bool isPartyMember(unsigned int chara);        // fn_710024BF60(chara, 10)
    static bool isPartyBattleMember(unsigned int chara);  // fn_710024BF60(chara, 3)
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it (1.0.0's isPartyMember tail-calls an unnamed
    // fn_71002AE6D4 too). A member because its only callers are isPartyMember and isPartyBattleMember, in this unit.
    // What it does: false for character 0; with mode 0 it looks the character up in the game data (drivers 1-16 at
    // 0x2C + (n - 1) * 0x5A0, 17-25 in GfDataManager::fn_7100224A10's 0xDAC-byte records, blades 1001-1013 against
    // GfBdatChrBl::getChrBlEnd) and tests the record's +0x20 short == 1 and fn_710023B1D8(chara); callers pass 10 and 3.
    static bool fn_710024BF60(unsigned int chara, unsigned int mode);
    static bool isLeader(unsigned int chara);  // false for 0
    static mm::Vec3* getSavePos(unsigned int index, bool flag);
    static mm::Vec3* getSaveRot(unsigned int index, bool flag);
};
}  // namespace gf

#endif
