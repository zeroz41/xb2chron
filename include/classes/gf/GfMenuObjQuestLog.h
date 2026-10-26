#ifndef CLASSES_GF_GFMENUOBJQUESTLOG_H
#define CLASSES_GF_GFMENUOBJQUESTLOG_H

#include "classes/gf/GfMenuObject.h"
#include "classes/gf/GfMenuReferenceQuest.h"
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
    bool seqTitleEndWait();
    bool seqLogStart();
    bool seqLogNextWaitInfo();
    bool seqLogNextEnd();
    bool seqOrderWait();

    unsigned char pad_24[4];
    // the quests the log shows: created in initialize (GfMenuReferenceQuest), released first in the destructor
    mm::mtl::IntrusivePtr<GfMenuReferenceQuest> m_quests[6];
    unsigned char pad_58[4];  // cleared by the constructor
    // the sequences' names are not the original's: seqTitleStart's (12 jobs), the log's (seqLogTaskComplete,
    // seqLogCloseEnd) and the order/complete windows' (seqOrderWaitCtrl, seqCompleteWaitCtrl)
    GfMenuSequence<GfMenuObjQuestLog, 12> m_titleSeq;
    GfMenuSequence<GfMenuObjQuestLog, 8> m_logSeq;
    GfMenuSequence<GfMenuObjQuestLog, 8> m_orderSeq;
    bool pad_940;  // cleared by the constructor
    int m_infoCtrl;  // seqLogNextWaitInfo waits for this control to finish (the name is not the original's)
    bool pad_948;  // cleared by the constructor; seqTitleFadeInText tests it
    // released (and cleared) by the destructor; the type is not known yet
    mm::mtl::ReferenceObject* pad_950;
    void* pad_958;  // cleared by the constructor
};
}  // namespace gf

#endif
