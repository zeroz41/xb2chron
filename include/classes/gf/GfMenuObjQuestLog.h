#ifndef CLASSES_GF_GFMENUOBJQUESTLOG_H
#define CLASSES_GF_GFMENUOBJQUESTLOG_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReferenceQuest.h"
#include "classes/gf/GfMenuReferenceNumber.h"
#include "classes/gf/GfMenuReferenceItem.h"
#include "gf/GfMenuSequence.h"
#include "mm/mtl/IntrusivePtr.h"

namespace gf { class QuestTaskParam; }
namespace gf { class GfMenuCallContext; }
#include "gf/QuestID.h"
namespace gf {
// table 0x7100B644A0
class GfMenuObjQuestLog : public ::gf::GfMenuObject {
public:
    static void completeTask(const QuestTaskParam& param);  // 1.0.0 symbol
    static void updateTask();  // 1.0.0 symbol
    static void lockLogOpen();  // 1.0.0 symbol
    static void unlockLogOpen();  // 1.0.0 symbol
    class CompleteListener;
    class LogListener;
    class OrderListener;
    class TitleListener;
    GfMenuObjQuestLog(unsigned int handle);
    virtual ~GfMenuObjQuestLog();  // slot 0
    // open the quest log for a quest just ordered / just completed, under a call context
    static void order(GfMenuCallContext* context, QuestID id);
    static void complete(GfMenuCallContext* context, QuestID id);
    static void openLog();
    static void closeLog();
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
    bool seqLogTaskComplete();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it is a job of this class's
    // sequences: OrderListener::reciveEvent queues it through Delegate<bool()>::memberFuncInvoker<GfMenuObjQuestLog>,
    // and it sits between that listener and seqOrderStart. What it does: GfMenuObjUtil::playJingle(6), returns true.
    bool fn_710046CDFC();
    // Placeholder name: new in 3.0.1, nothing in 1.0.0's place names it. A member because it is a job of this class's
    // sequences: seqTitleStart queues it twice, and it sits between seqCompleteStart and seqTitleFadeInText. What it
    // does: GfMenuObjUtil::playJingle(7), returns true.
    bool fn_710046D648();
    bool seqTitleStart();  // TitleListener queues it
    bool seqTitleEndWait();
    bool seqLogStart();
    bool seqLogNextWaitInfo();
    bool seqLogNextEnd();
    bool seqOrderWait();
    void setupLogClear();
    bool seqLogOut();
    bool seqTitleFadeInText();
    bool seqTitleFadeInScenario();
    bool seqTitleFadeOutScenario();
    bool seqTitleFadeInNormal();
    bool seqTitleFadeOutNormal();
    bool seqLogIn();
    bool seqOrderStart();
    bool seqLogNext();
    void setupLog();
    void setupLogItem();
    bool seqLogClose();
    bool seqLogCloseEnd();
    bool seqOrderActivation();
    bool seqOrderWaitCtrl();
    bool seqCompleteStart();  // CompleteListener queues it
    bool seqCompleteWaitCtrl();
    bool seqCompleteWait();

    unsigned char pad_24[4];
    // the references the log's UI shows, created in initialize and released first in the destructor (one loop):
    // 0-2 GfMenuReferenceQuest, 3-4 GfMenuReferenceNumber, 5 GfMenuReferenceItem (the name is not the original's)
    mm::mtl::IntrusivePtr<mm::mtl::ReferenceObject> m_refs[6];
    // the reference at that index as its class (operator->'s assert; the name is not the original's)
    template <typename R>
    R* getRef(int index) const {
        return static_cast<R*>(m_refs[index].operator->());
    }
    unsigned char pad_58;  // cleared by the constructor
    // the log is open: set by seqLogOpen once its animation ends, cleared by seqLogCloseEnd (setupLog then updates
    // LAY_log_to_detail; the name is not the original's)
    bool m_logOpened;
    bool pad_5A;           // cleared by the constructor; seqLogCloseEnd queues seqLogOut when set
    // setupLog: the quest is visible in the quest list (shows LAY_log_to_detail; the name is not the original's)
    bool m_listVisible;
    // the sequences' names are not the original's: seqTitleStart's (12 jobs), the log's (seqLogTaskComplete,
    // seqLogCloseEnd) and the order/complete windows' (seqOrderWaitCtrl, seqCompleteWaitCtrl)
    GfMenuSequence<GfMenuObjQuestLog, 12> m_titleSeq;
    GfMenuSequence<GfMenuObjQuestLog, 8> m_logSeq;
    GfMenuSequence<GfMenuObjQuestLog, 8> m_orderSeq;
    bool pad_940;  // cleared by the constructor
    int m_infoCtrl;  // seqLogNextWaitInfo waits for this control to finish (the name is not the original's)
    bool pad_948;  // cleared by the constructor; seqTitleFadeInText tests it
    // the reward window's call context: CompleteListener creates it on the first complete event (0x21) and opens
    // GfMenuObjQuestReward under it; the destructor releases it (the name is not the original's)
    GfMenuCallContext* m_rewardContext;
    // setupLog: the quest's task count (GfQuestInfo::getQuestTaskInfo; the name is not the original's)
    unsigned int m_taskCount;
    unsigned char pad_95C[4];
};
}  // namespace gf

#endif
