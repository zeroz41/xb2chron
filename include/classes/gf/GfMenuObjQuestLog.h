#ifndef CLASSES_GF_GFMENUOBJQUESTLOG_H
#define CLASSES_GF_GFMENUOBJQUESTLOG_H

#include "classes/gf/GfMenuObject.h"

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
    virtual ~GfMenuObjQuestLog();  // slot 0
    // open the quest log for a quest just ordered / just completed, under a call context
    static void order(GfMenuCallContext* context, QuestID id);
    static void complete(GfMenuCallContext* context, QuestID id);
    virtual void initialize();  // slot 2
    virtual void finalize();  // slot 3
    virtual void update();  // slot 4
};
}  // namespace gf

#endif
