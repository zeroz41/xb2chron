#ifndef CLASSES_GF_GFPLAYCOMQUESTORDERUI_H
#define CLASSES_GF_GFPLAYCOMQUESTORDERUI_H

#include "classes/gf/GfPlayCom.h"
#include "gf/QuestID.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf {
// table 0x7100B58028
class GfPlayComQuestOrderUI : public GfPlayCom {
public:
    static GfPlayComQuestOrderUI* create(QuestID id, bool flag);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComQuestOrderUI();  // slot 1
    virtual const char* getFuncName() const;  // slot 3
    virtual void start();  // slot 4
    virtual void vf5();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
};
}  // namespace gf

#endif
