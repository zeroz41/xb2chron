#ifndef CLASSES_GF_GFPLAYCOMQUESTORDERUI_H
#define CLASSES_GF_GFPLAYCOMQUESTORDERUI_H

#include "classes/gf/GfPlayCom.h"
#include "gf/QuestID.h"
#include "mm/mtl/RTTI.h"
namespace fw { class UpdateInfo; }

namespace gf { class GfMenuCallContext; }
namespace gf {
// table 0x7100B58028
class GfPlayComQuestOrderUI : public GfPlayCom {
public:
    // the field names are not the original's
    GfPlayComQuestOrderUI(QuestID id, bool flag) : GfPlayCom(34, false), m_id(id), m_flag(flag), m_context(nullptr) {}
    static GfPlayComQuestOrderUI* create(QuestID id, bool flag);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual ~GfPlayComQuestOrderUI();  // slot 1
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "QuestOrderUI";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    static mm::mtl::RTTI m_rtti;
    QuestID m_id;
    bool m_flag;                     // create's second argument; nothing here reads it
    GfMenuCallContext* m_context;    // start() creates it for the quest log; the destructor releases it
};
}  // namespace gf

#endif
