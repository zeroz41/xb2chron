#ifndef CLASSES_GF_GFPLAYCOMQUESTCOMPLETEUI_H
#define CLASSES_GF_GFPLAYCOMQUESTCOMPLETEUI_H

#include "classes/gf/GfPlayCom.h"
#include "gf/QuestID.h"
#include "gf/GfQuestInfo.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B58070
class GfPlayComQuestCompleteUI : public GfPlayCom {
public:
    static GfPlayComQuestCompleteUI* create(QuestID id, QuestID next, QSTATE state);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComQuestCompleteUI();  // slot 1
    virtual const char* getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void vf5();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
