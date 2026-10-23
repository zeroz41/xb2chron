#ifndef GF_GFDATAMERCENARIES_H
#define GF_GFDATAMERCENARIES_H

namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace gf {
// a mission's blade condition (GfDataMercenaries::getRequestCondition fills it; the field names are not the
// original's, they follow GfMenuMissionAdapter's update_MissionCond* callbacks)
struct GfRequestBladeData {
    int m_type;   // 1..7 (update_MissionCondIcon shows m_type - 1)
    int m_param;  // update_MissionCondParamIcon's icon (types 1, 3, 4)
    int m_level;  // update_MissionCondParam (type 2), update_MissionCondLv (types 5, 6)
    int m_count;  // the blades it needs (0 counts as 1)
};

// the mercenary team's data (functions, by its symbols)
class GfDataMercenaries {
public:
    // a team, as the game data keeps them (0x28 bytes); the name is not the original's
    struct Team {
        unsigned char pad_0[0x10];
        unsigned int m_teamId;  // what the functions that take a team id are given for it
        unsigned char pad_14[0x14];
    };
    static int getLevel();  // up to 5 (GfMenuGameAdapter::update_MercenariesPoint shows no points at 5)
    static int getPoint();
    static int getPointMax();
    static unsigned int getTeamNum();
    static Team* getTeamByIndex(unsigned int index);
    static bool isTeamStateReward(unsigned int teamId);  // the team is back with a reward to collect
    // the teams on a zone's missions, working on them or done with them
    static void getTeamByZoneMissionWorking(mm::mtl::FixedVector<unsigned short, 3>& teams, unsigned int zone);
    static void getTeamByZoneMissionComplete(mm::mtl::FixedVector<unsigned short, 3>& teams, unsigned int zone);
    static bool isTeamStateExpedition(unsigned int teamId);  // the team is away on a mission
    static int getMissionCategory(unsigned int mission);
    static bool isNewMission(unsigned int mission);
    static unsigned int getTeamIDByMissionID(unsigned int mission);  // 0 when no team is on it
    static bool isMissionComplete(unsigned int mission);
    static bool isMissionCompleteFlag(unsigned int mission);
    static bool isMissionOrderParty(unsigned int mission);
    static bool isMissionOrderTeam(unsigned int mission);
    static bool isOrderOnlyOne(unsigned int mission);
    // a mission's message ids: its title, its zone
    static bool getMsgTitleName(unsigned char*& bdat, unsigned int& id, unsigned int mission);
    static bool getMsgZoneName(unsigned char*& bdat, unsigned int& id, unsigned int mission);
    static bool getFieldSkillInfo(unsigned char*& bdat, unsigned int& id, unsigned int mission, unsigned int slot);
    static unsigned int getFieldSkill(unsigned int mission, unsigned int slot);
    static bool getRequestCondition(GfRequestBladeData& data, unsigned int mission, unsigned int slot);
};
}  // namespace gf

#endif
