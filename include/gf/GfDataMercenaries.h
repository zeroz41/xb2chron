#ifndef GF_GFDATAMERCENARIES_H
#define GF_GFDATAMERCENARIES_H

namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}
#include "classes/gf/GfFieldTime.h"
#include "gf/QuestID.h"

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
    // SCOM_POPUP::createMercenaryAdd puts it in its popup
    static unsigned int getMissionMapID(unsigned int mission);
    // a team, as the game data keeps them (0x28 bytes); the name is not the original's
    struct Team {
        unsigned short m_members[6];  // its blades (getTeamMember; getTeamLeader reads the first)
        unsigned char pad_c[0x4];
        unsigned int m_teamId;  // what the functions that take a team id are given for it
        unsigned int m_mission;  // the mission it is on, 0 for none (getTeamMission; the name is not the original's)
        unsigned char pad_18[0x4];
        ElapseTime m_missionTime;  // getTeamMissionTime(teamId) (the name is not the original's)
        unsigned char pad_20[0x8];
    };
    static int getLevel();  // up to 5 (GfMenuGameAdapter::update_MercenariesPoint shows no points at 5)
    static int getPoint();
    static int getPointMax();
    static unsigned int getTeamNum();
    static Team* getTeamByIndex(unsigned int index);
    static Team* getTeamByTeamID(unsigned int teamId);
    static Team* getTeamByMissionID(unsigned int mission);
    static bool isTeamStateEmpty(unsigned int teamId);
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
    static unsigned int getFieldSkill1(unsigned int mission);
    static unsigned int getFieldSkill2(unsigned int mission);
    static unsigned int getFieldSkill3(unsigned int mission);
    static unsigned int getStartMissionID();
    static QuestID getMissionQuestID(unsigned int mission);
    static unsigned int getMissionTime(unsigned int mission);
    static bool getRequestCondition(GfRequestBladeData& data, unsigned int mission, unsigned int slot);
    static bool isValidTeamID(unsigned int teamId);
    static unsigned int getTeamLeader(unsigned int teamId);  // the team's leader blade, 0 for none
    static unsigned int getTeamMission(unsigned int teamId);  // the mission the team is on, 0 for none
    static unsigned int getMissionZoneID(unsigned int mission);
    static ElapseTime getTeamMissionTime(unsigned int teamId);  // the time the team's mission still takes
    static unsigned int getTeamPower(unsigned int teamId);
    static int getTeamMaleNum(unsigned int teamId);
    static int getTeamFemaleNum(unsigned int teamId);
    static int getTeamAnimalNum(unsigned int teamId);
    static unsigned short* getTeamMember(unsigned int teamId);  // the team's six blades
    static unsigned int getTeamID(unsigned int blade);  // the team the blade is in, 0 for none
    static unsigned int getPointLimit();
    static void setLevel(unsigned int level);
    static void setPoint(unsigned int point);
    static unsigned int getMissionFlag(unsigned int mission);
    static void setMissionCompleteFlag(unsigned int mission);
    static void clearNewMission(unsigned int mission);
    static unsigned int getLevelMax();
};
}  // namespace gf

#endif
