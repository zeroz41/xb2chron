#ifndef CLASSES_GF_GFGAMEMERCENARIES_H
#define CLASSES_GF_GFGAMEMERCENARIES_H

#include "classes/mm/mtl/PtrSingleton.h"

namespace gf { class GfGameMercenaries; }
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }
namespace gf { class QuestOrderParam; }
namespace mm { namespace mtl { template <typename, unsigned long> class FixedVector; }}

namespace gf {
// table 0x7100B56D30
class GfGameMercenaries : public ::mm::mtl::PtrSingleton< ::gf::GfGameMercenaries> {
public:
    // SCOM_ADD_MERCENARIES_POINT and SCOM_SET_MERCENARIES_LEVEL pass their request's value
    static void addPoint(unsigned int point);
    static void setLevel(unsigned int level);
    // SCOM_MISSION_COMPLETE (the mission): 3 runs the reward, 2 completes it by force
    static int getMissionFlag(unsigned int mission);
    static void execMissionReward(unsigned int mission);
    static void setMissionCompleteForce(unsigned int mission);
    static void execMissionRewardAchievementBonusForBlade(unsigned int mission);
    static void execMissionAchievementForBlade(unsigned int mission);
    static void clearTeamMember(unsigned int team);
    virtual ~GfGameMercenaries();  // slot 0
    static void qevOrderQuest(const gf::QuestOrderParam&);
    // a mission's rewards (team: GfDataMercenaries::isMissionOrderTeam), the bonus parts ("Hosei") on their own
    static int getRewardGold(unsigned int mission, bool team);
    static int getRewardGoldHosei(unsigned int mission, bool team);
    static int getRewardExp(unsigned int mission, bool team);
    static int getRewardDevelop(unsigned int mission, bool team);
    static int getRewardDevelopHosei(unsigned int mission, bool team);
    static int getRewardTrust(unsigned int mission);
    static int getRewardMercenariesPoint(unsigned int mission);
    static void getZoneMission(mm::mtl::FixedVector<unsigned short, 500>& missions, unsigned int zone);  // a zone's missions
    static void qevCompleteQuest(const gf::QuestCompleteParam& param);
    static void gevMapjump(gf::GEV gev, const gf::MapjumpCallbackInfo& info);
    static void gevMercenariesMissionFlag(unsigned int, unsigned int, unsigned int);
};
}  // namespace gf

#endif
