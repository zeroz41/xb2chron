#ifndef CLASSES_GF_GFQUESTMANAGER_H
#define CLASSES_GF_GFQUESTMANAGER_H

#include "classes/mm/mtl/PtrSingleton.h"
#include "gf/QuestID.h"
#include "gf/QuestListAcc.h"
#include "mm/mtl/FixStr.h"
#include "mm/mtl/FixedQueue.h"
#include "gf/GfQuestInfo.h"
#include "gf/GfQuestReward.h"

namespace gf { class GfQuestManager; }
namespace gf { enum GEV : int; class MapjumpCallbackInfo; class QuestCompleteParam; class QuestCompleteChildParam; }
namespace gf { class GfSetupParam; class IQuestEvent; class GfBdatQuest; class GfQuestEvent; class GfQuestTarget; }
namespace fw { class UpdateInfo; }

namespace gf { enum RELOAD_BDAT : int; }
namespace gf {
// an element of GfQuestManager's order queues (FixedQueue<gf::QuestData, 8000>::insert's signature names it): 4
// bytes, the quest (getOrderQuest(unsigned) returns it)
class QuestData {
public:
    QuestID m_id;  // the name is not the original's
};

// table 0x7100B56DB0
class GfQuestManager : public ::mm::mtl::PtrSingleton< ::gf::GfQuestManager> {
public:
    GfQuestManager(const GfSetupParam& param);
    static void build(const GfSetupParam& param);
    static void destroy();
    static void resetQuest(QuestID id);
    void destroyEvent();
    static void addEvent(IQuestEvent* event);
    static void removeEvent(IQuestEvent* event);
    static ::mm::mtl::FixedQueue<QuestData, 15000>* getOrderAchievementQuest();
    static ::mm::mtl::FixedQueue<QuestData, 8000>* getOrderQuest();
    static void update(const fw::UpdateInfo& info);
    void updateOrderQuest();
    static void updateCurrentTaskCondition();
    void refreshOrderQuestList();
    void setupParallelTaskCheck();
    void setupAchievementTaskCheck();
    void addEntryQuest(QuestID id);
    static void refreshQuestTaskState();
    static void eventCheckTaskAll();
    static void eventChangeCurrentQuest(QuestID before, QuestID after);
    static void setCurrentQuest(QuestID id);
    // members whose bodies never use this: callers pass any value (setCurrentQuest passes what its call left in x0)
    // members whose bodies never use this: setCurrentQuest calls them with whatever x0 holds (clang passes undef for
    // the dead this), and they take the quest in w1
    void setCurrentQuestScenario(QuestID id);
    void setCurrentQuestSelect(QuestID id);
    static void setCurrentQuestForScenario();
    static QuestID getPrevCompleteQuest();
    static QuestID getLastOrder();
    static unsigned int getOrderQuestMax();
    static unsigned int getOrderQuestMaxWithAchievement();
    static QuestID getOrderQuest(unsigned int index);
    // the ordered quest of the purpose (GfQuestUtil::addTaskHanyouCount)
    static QuestID getOrderQuestId(unsigned int purposeId);
    static unsigned int getReduceHpQuestMax();
    static QuestID getReduceHpQuest(unsigned int index);
    static void requestOrderAchievementQuestForce();
    static void resetBattleTaskForPlayerDead();
    static QuestID getOrderQuestWithAchievement(unsigned int index);
    static void requestOrderQuestForce();
    static void gevBattleEnd();
    static void gevPlayEvent(GEV gev, unsigned int id);
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
    // GfQuestTask::setupOrderTask passes an affinity chart quest and updateQuestTask's state (2 or more) when its
    // level is complete
    // fn_710030EB68 passes a collect task whose count changed
    static void eventChangeTaskState(const QuestTaskParam& param);
    static void checkQuestComplete(gf::QuestID id, gf::QSTATE state);

    static GfQuestManager* s_pThis;
    static GfBdatQuest* s_bdat;
    static GfQuestEvent* s_event;
    static GfQuestTarget* s_target;

    // the field names below are not the original's: each is named after the functions that use it
    ::mm::mtl::FixedQueue<IQuestEvent*, 16> m_events;  // addEvent, removeEvent
    // the constructor sets it last, destroy clears it (the name is not the original's)
    bool m_active;
    ::mm::mtl::FixedQueue<QuestData, 8000> m_orderQuest;  // getOrderQuest
    ::mm::mtl::FixedQueue<QuestData, 15000> m_orderAchievementQuest;  // getOrderAchievementQuest
    unsigned char pad_16820[0x2DF50 - 0x16820];
    ::mm::mtl::FixedQueue<QuestID, 128> m_completeQuest;  // getPrevCompleteQuest reads its last (name not original)
    unsigned char pad_2E160[0x2E780 - 0x2E160];
    QuestID m_lastOrder;  // getLastOrder
    unsigned char pad_2E784[0x3F428 - 0x2E784];
    ::mm::mtl::FixedQueue<QuestID, 1024> m_reduceHpQuest;  // getReduceHpQuest (the name is not the original's)
    unsigned char pad_40438[0x41640 - 0x40438];
    // set by requestRefreshQuestTaskState, requestOrderAchievementQuestForce and requestOrderQuestForce (the names
    // are not the original's)
    bool m_requestRefreshQuestTaskState;
    bool m_requestOrderAchievementQuest;
    bool m_requestOrderQuest;
};
}  // namespace gf

#endif
