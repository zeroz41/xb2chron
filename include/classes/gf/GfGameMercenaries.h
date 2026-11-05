#ifndef CLASSES_GF_GFGAMEMERCENARIES_H
#define CLASSES_GF_GFGAMEMERCENARIES_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "mm/mtl/FixedVector.h"
#include "gf/QuestID.h"
#include "gf/GfDataMercenaries.h"
#include "gf/QuestCompleteParam.h"

namespace gf { class GfGameMercenaries; class GfSetupParam; }
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }
namespace gf { class QuestOrderParam; }
// the reward slot getRewardItem reads (an index into GfQuestReward::m_items; unsigned: the original zero-extends it)
namespace gf { enum QUEST_REWARD : unsigned int; }
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B56D30
class GfGameMercenaries : public ::mm::mtl::PtrSingleton< ::gf::GfGameMercenaries> {
public:
    // the constructor, initialize, finalize, getTeam and applyCompleteMission are inline: 3.0.1's symbols name no
    // copy of them (1.0.0's do)
    GfGameMercenaries(const GfSetupParam& param) : m_initialized(false), m_stopMissionTime(false) {
        initialize(param);
    }
    void initialize(const GfSetupParam&) {
        rebuildAutoStartList();
        m_initialized = true;
    }
    void finalize() { m_initialized = false; }
    virtual ~GfGameMercenaries();  // slot 0
    static void build(const GfSetupParam& param);
    static void destroy();
    void rebuildAutoStartList();
    static void update(const fw::UpdateInfo& info);
    void updateMercenariesTeam(const fw::UpdateInfo& info);
    // the teams' ids, in GfDataMercenaries' order
    static void getTeam(mm::mtl::FixedVector<unsigned short, 3>& teams) {
        for (unsigned int i = 0; i < GfDataMercenaries::getTeamNum(); i++) {
            teams.push_back(GfDataMercenaries::getTeamByIndex(i)->m_teamId);
        }
    }
    static void checkTeamMissionComplete();
    static void updateMissionAutoStart();
    static void addPoint(unsigned int point);
    static void setLevel(unsigned int level);
    // SCOM_MISSION_COMPLETE (the mission): 3 runs the reward, 2 completes it by force
    static int getMissionFlag(unsigned int mission);
    static void setMissionComplete(unsigned int mission);
    static void setMissionFlag(unsigned int mission, unsigned int flag);
    static void execMissionReward(unsigned int mission);
    static void setMissionCompleteForce(unsigned int mission);
    static void execMissionRewardAchievementBonusForBlade(unsigned int mission);
    static void execMissionAchievementForBlade(unsigned int mission);
    static void execMissionRewardByTeamID(unsigned int teamId);  // the reward of the team's mission
    // placeholder (it sits between addTeamMember and clearTeamMember; callers: clearTeamMember (false) and
    // clearTeamMemberForHana (GfDataHana::isValid(blade))): after the game is cleared, re-activates blades 0x3E9..0x3EB
    // for blades 0x3E9/0x3EA and, for a Hana blade, each Hana form 0x3ED..0x3EF marked mercenary-unuse 1..3
    static void fn_71003014CC(unsigned int blade, bool hana);
    static void clearTeamMember(unsigned int team);
    static void clearTeamMemberForHana(unsigned int team);  // (symbols)
    // (symbols) adds the blade to the team; GfMenuObjMercenaryForm::seqDepartureEnd adds each of its team list's
    static bool addTeamMember(unsigned int teamId, unsigned int blade);
    static bool getZoneMission(mm::mtl::FixedVector<unsigned short, 500>& missions, unsigned int zone);  // a zone's missions
    static bool orderMission(unsigned int teamId, unsigned int mission);
    static void cancelMission(unsigned int mission);  // (symbols)
    static void qevOrderQuest(const gf::QuestOrderParam& param);
    static void qevCompleteQuest(const gf::QuestCompleteParam& param);
    void applyCompleteMission(const gf::QuestCompleteParam& param) {
        unsigned int mission = GfDataMercenaries::getMissionByQuestID(param.m_questId);
        if (mission != 0 && GfDataMercenaries::getMissionFlag(mission) == 2) {
            setMissionComplete(mission);
        }
    }
    void applyMercenariesLevel(const gf::QuestCompleteParam& param);
    static void applyDestroyMission();
    static void gevMercenariesMissionFlag(unsigned int mission, unsigned int flag, unsigned int old);
    static bool isQuestMission(QuestID quest);
    // a mission's rewards (team: GfDataMercenaries::isMissionOrderTeam), the bonus parts ("Hosei") on their own
    static int getRewardGold(unsigned int mission, bool team);
    static int getRewardGoldHosei(unsigned int mission, bool team);
    static int getRewardExp(unsigned int mission, bool team);
    static int getRewardDevelop(unsigned int mission, bool team);
    static int getRewardDevelopHosei(unsigned int mission, bool team);
    static int getRewardTrust(unsigned int mission);
    static int getRewardMercenariesPoint(unsigned int mission);
    // the reward slot's item (its low and high halves), false when there is none
    static bool getRewardItem(unsigned int& item, unsigned int& count, unsigned int mission, QUEST_REWARD slot);
    // 2.0.0 names it (1.0.0's body there is empty); unless GfGameManager::isGameTypeIra(), sets every mission's
    // flag (GfDataMercenaries' start to end mission) to 0 through setMissionFlag
    static void setupNewGameParam();
    static void stopMissionTime(bool stop);
    static void gevMapjump(gf::GEV gev, const gf::MapjumpCallbackInfo& info);

    bool m_initialized;  // set by initialize, cleared by finalize (1.0.0's isInitialized reads it)
    // only the destructor touches it: the element type is not proven (any 2-byte type fills it exactly)
    mm::mtl::FixedVector<unsigned short, 424> pad_10;
    unsigned char pad_368[0x18];
    // the missions QuestListAcc::getFLD_MercenariesMissionAutoStart marks (rebuildAutoStartList)
    mm::mtl::FixedVector<unsigned short, 512> m_autoStartList;
    bool m_stopMissionTime;  // stopMissionTime's flag: updateMercenariesTeam does not run the teams' time
};
}  // namespace gf

#endif
