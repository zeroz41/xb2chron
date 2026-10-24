#ifndef CLASSES_GF_GFQUESTMANAGER_H
#define CLASSES_GF_GFQUESTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/QuestID.h"
#include "gf/QuestListAcc.h"
#include "mm/mtl/FixStr.h"
#include "gf/GfQuestInfo.h"
#include "gf/GfQuestReward.h"

namespace gf { class GfQuestManager; }
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }

namespace gf { enum RELOAD_BDAT : int; }
namespace gf {
// table 0x7100B56DB0
class GfQuestManager : public ::mm::mtl::PtrSingleton< ::gf::GfQuestManager> {
public:
    // SCOM_REFRESH_COMPASS's and SCOM_BATTLE_TASK_RESET's requests, three frames after they are made
    static void requestRefreshQuestTaskState();
    static void setCompleteQuest(QuestID id, QuestID next, QSTATE state);
    static void resetBattleTaskForBattleEnd();
    static void gevReloadBdat(RELOAD_BDAT, unsigned int);
    static void gevChangeWeather(unsigned int, unsigned int);
    static void gevChangeTimeRange(unsigned int);
    static void gevItemAdd(unsigned int, int);
    virtual ~GfQuestManager();  // slot 0
    static void entryOrderAchievQuest(gf::QuestID id);
    // whether the quest's order opened (GfQuestEvent::setQuestEntry tests it)
    static bool openOrder(gf::QuestID id, bool notify);
    static bool getRewardItem(GfQuestReward& reward, gf::QuestID id, bool);
    static gf::QuestID getCurrentQuest(QTYPE type);
    static void eventChangeQuestState(gf::QuestID id, gf::QSTATE before, gf::QSTATE after);
    static void addCompleteQuest(gf::QuestID id);
    static gf::QuestID getProgressCurrentQuest(gf::QTYPE type);
    static void gevMapjump(gf::GEV gev, const gf::MapjumpCallbackInfo& info);
    static void gevMercenariesMissionFlag(unsigned int, unsigned int, unsigned int);
    static void eventCheckTask(gf::QuestID id);
};
}  // namespace gf

#endif
