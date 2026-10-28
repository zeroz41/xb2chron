#ifndef CLASSES_GF_GFPLAYCOMFIELDTBOX_H
#define CLASSES_GF_GFPLAYCOMFIELDTBOX_H

#include "classes/gf/GfPlayCom.h"
#include "classes/mm/mtl/PtrSingleton.h"
#include "classes/gf/GfGameScene.h"
#include "gf/QuestID.h"
namespace gf { class GF_OBJ_HANDLE; }

namespace gf {
// table 0x7100B57E60; GfSequentialPlay::addFieldTbox makes it
class GfPlayComFieldTbox : public GfPlayCom, public mm::mtl::PtrSingleton<GfPlayComFieldTbox> {
public:
    explicit GfPlayComFieldTbox(GF_OBJ_HANDLE* handle);  // out of line (0x710031B12C)
    static GfPlayComFieldTbox* create(GF_OBJ_HANDLE* handle);
    virtual const mm::mtl::RTTI* getRTTI() const { return &m_rtti; }  // slot 0
    virtual const char* getFuncName() const {  // slot 3
        static const char* func = "PlayComFieldTbox";
        return func;
    }
    virtual void start();  // slot 4
    virtual void end();  // slot 5
    virtual bool update(const fw::UpdateInfo& info, bool flag);  // slot 6
    // whether GfFieldTbox's open sequence is over: no step left, or the field skill menu is gone and the controlled
    // mover's first animation layer is back in "S_idle" (the name is from the symbols)
    bool isOpenFinish() const;
    static mm::mtl::RTTI m_rtti;

    unsigned int m_pause;  // from GfGameScene::createPlayerPause
    GF_OBJ_HANDLE* m_handle;
    // the quest whose task the box belongs to (GfQuestUtil::getCurrentTBoxWithEvent; cleared for a dig box not dug
    // yet); the name is not the original's
    QuestID m_quest;
    // update's step: 0 waits for the box to open, 1 waits for m_quest to finish, 2 for the drop items (the name is
    // not the original's)
    int m_step;
    float m_time;  // seconds in steps 1 and 2 (the name is not the original's)
    unsigned char pad_34[0x4];
};
}  // namespace gf

#endif
