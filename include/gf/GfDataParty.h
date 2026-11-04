#ifndef GF_GFDATAPARTY_H
#define GF_GFDATAPARTY_H

namespace mm { class Vec3; }

namespace gf {
struct SDataParty;

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
    // the driver of the member at an index of a party (0: the game data's party at 0xE9884, 1 and 2 the other two
    // parties GfDataManager::getDataGameIra keeps at 0x10D04 and 0x10D40). The symbols spell it fn_7100238EC8: 1.0.0's
    // GfDataParty::getDriver(unsigned int) has the same body for party 0, sits next to GfDataDriver::getBlade as this
    // does, and 1.0.0's GfMenuObjUtil::isBladeEnableOffset calls it where 3.0.1's calls fn_7100238EC8 (3.0.1 added the
    // second parameter, as for getPartyMember; its name is not the original's)
    static unsigned int getDriver(unsigned int index, unsigned int party);
    // the party index of a driver (0.., -1 for 0 or a driver not in the party). The symbols spell it fn_710023B1D8:
    // 1.0.0's GfDataParty::getDriverPartyID(unsigned int) sits right after GfDataBlade::isActivateParty as this does,
    // has the same shape (0 -> -1, then the game data's party records from 0xE9884 compared one by one) and the same
    // callers (GfAssetSetupBlade::setup, DataObjBlade::getBladeSet, GfDataBlade's party lists)
    static int getDriverPartyID(unsigned int driver);
    static bool isRideChar(unsigned int chara);
    // whether a driver is one of the first three party members' drivers
    static bool isExistDriver(unsigned int driver);
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
    // 0x2C + (n - 1) * 0x5A0, 17-25 in GfDataManager::getDataGameIra's 0xDAC-byte records, blades 1001-1013 against
    // GfBdatChrBl::getChrBlEnd) and tests the record's +0x20 short == 1 and fn_710023B1D8(chara); callers pass 10 and 3.
    static bool fn_710024BF60(unsigned int chara, unsigned int mode);
    static bool isLeader(unsigned int chara);  // false for 0
    static mm::Vec3* getSavePos(unsigned int index, bool flag);
    static mm::Vec3* getSaveRot(unsigned int index, bool flag);
    static bool empty();  // no driver in the first three members
    // 2.0.0's symbols name it. What it does: whether the driver of the game data's party member at index
    // (SDataParty::m_members) has blade in one of its getMaxSetBladeNum slots (GfDataDriver::getBlade). Callers:
    // GfAssetSetupBlade::setup, GfDataBlade::fn_71002356BC and getListParty.
    static bool isExistBlade(unsigned int index, unsigned int blade);
    // 2.0.0's symbols name it. What it does: handle unchanged unless driver is a DLC driver (0x11..0x19); then
    // fn_710024BCEC(driver) 1 or 2 gives getFixedHandleForBlade(handle, 0 or 1). Caller: GfObjFactory::createDriver.
    static unsigned int getFixedHandleForDriver(unsigned int handle, unsigned int driver);
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member for the same reason as
    // getFixedHandleForDriver (its only caller). What it does: takes the driver's CHR_Ir row (GfBdatChrDr::getChrDrIraParam) and
    // its GroupID, then counts the CHR_Ir rows of that group before the row whose driverID is the driver
    // (0 for no row or no match).
    static unsigned int fn_710024BCEC(unsigned int driver);
};

// the party's part of the game data (GfDataParty::getSDataParty points at it); the name is not the original's
struct SDataParty {
    // its first members (GfDataParty::empty tests the first three's drivers; the count is not known)
    GfDataParty::PartyMember m_members[3];
    unsigned char pad_12[0x2A];
    // 0x3C: the kind of id m_leader holds (GfGameParty::getLeaderLevel: 4 looks the member up with getPartyId(4, id),
    // 3 takes it as the driver id); the name is not the original's
    unsigned int m_leaderType;
    unsigned int m_leader;  // 0x40: GfDataParty::isLeader compares a character with it (the name is not the original's)
    unsigned char pad_44[0x8];
    unsigned short m_partyGauge;  // GfGameParty::getPartyGauge and setPartyGauge (300 full)
};
}  // namespace gf

#endif
