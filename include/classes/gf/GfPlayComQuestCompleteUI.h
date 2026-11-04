#ifndef CLASSES_GF_GFPLAYCOMQUESTCOMPLETEUI_H
#define CLASSES_GF_GFPLAYCOMQUESTCOMPLETEUI_H

#include "classes/gf/GfPlayCom.h"
#include "gf/QuestID.h"
#include "gf/GfQuestInfo.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf { class GfMenuCallContext; }
namespace gf {
// table 0x7100B58070
class GfPlayComQuestCompleteUI : public GfPlayCom {
public:
    // counts itself in s_active (the field names are not the original's)
    GfPlayComQuestCompleteUI(QuestID id, QuestID next, QSTATE state)
        : GfPlayCom(35, false), m_id(id), m_next(next), m_state(state), m_context(nullptr) {
        s_active++;
    }
    static GfPlayComQuestCompleteUI* create(QuestID id, QuestID next, QSTATE state);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComQuestCompleteUI();  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "QuestCompleteUI";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    static int s_active;  // live commands: the constructor counts up, the destructor down
    // started commands: start() counts up, end() down (2.0.0's symbols name it)
    static int s_disp;
    QuestID m_id;
    QuestID m_next;
    QSTATE m_state;
    GfMenuCallContext* m_context;  // start() creates it for the quest log; the destructor releases it
};
}  // namespace gf

#endif
